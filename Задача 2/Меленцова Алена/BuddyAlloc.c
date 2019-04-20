#include <string.h>
#include <stdio.h>
#include "BuddyAlloc.h"

buddy_allocator_t *constructor(size_t raw_memory_size)
{
	buddy_allocator_t * newBuddy = (buddy_allocator_t *)malloc(sizeof(buddy_allocator_t)); //создали структуру
	if (NULL == newBuddy)
	{
		printf("Failed to allocate memory.\n");
		return NULL;
	}
	memset(newBuddy, 0, sizeof(buddy_allocator_t)); //в newBuddy заполняем 0 размер buddy_allocator_t
	newBuddy->memStart = malloc(raw_memory_size); // начало выделенной памяти, malloc  тоже указывает на начало
	if (NULL == newBuddy->memStart)
	{
		printf("Failed to allocate memory.\n");
		free(newBuddy); //очистили
		return NULL;
	}
	memset(newBuddy->memStart, 0, raw_memory_size); //снова забиваем 0 размер raw_memory_size начиная с memStart
	newBuddy->memSize = raw_memory_size;
	if (!initBuddyAlloc(newBuddy)) //если размер аллокатора > 2^34, если не удалось создать пул и положить по степени старт куска, то очистили все
	{
		free(newBuddy->memStart);
		free(newBuddy);
		return NULL;
	}
	// нода - список связности(кладем туда аллокаторы)
	node * newNode = (node *)malloc(sizeof(node)); //выделили память под ноду
	newNode->buddy_alloc = newBuddy; //у ноды определили ее блок
	newNode->next = NULL; // следующий пока неизвестен

	if (NULL == buddyList)
		buddyList = newNode; //указатель на голову списка связности
	else
	{
		node * ptr = buddyList;
		while (ptr->next != NULL) //идем от головы до самого последнего и добавляем новый элемент
		{
			ptr = ptr->next;
		}
		ptr->next = newNode;
	}

	return newBuddy;
}

void buddy_allocator_destroy(buddy_allocator_t *buddy_allocator) // зачищаем сам аллокатор
{
	node * ptr = buddyList;
	node * prev = NULL;

	while (ptr != NULL && ptr->buddy_alloc != buddy_allocator) 
	{
		prev = ptr;
		ptr = ptr->next;
	}

	if (ptr != NULL) //если дошли до нашего аллокатора
	{
		if (NULL == prev) // если лежит единственный наш аллокатор
		{
			buddyList = ptr->next;
		}
		else 
		{
			prev->next = ptr->next; //вырезали наш аллокатор, изменив ссылки
		}
		free(buddy_allocator->memStart); //free освобождает выделенную до этого malloc память
		buddy_allocator->memStart = NULL;
		free(buddy_allocator);
		buddy_allocator = NULL;
		free(ptr);
		ptr = NULL;
	}
}

int initBuddyAlloc(buddy_allocator_t *buddy_allocator)
{
	uint8_t order = 0; //степень
	while (ORDERTOSIZE(order) < buddy_allocator->memSize) // пока степень 2 меньше того, что хотим выделить
	{
		order++;
	}

	if (order > MAX_ORDER) //максимальная степень 34
	{
		printf("Cannot create buddy allocator as backup memory is more than can be supported\n");
		return FAIL;
	}

	buddy_allocator->maxOrder = order; //определили степень всего изначально выделенного куска
	memset(buddy_allocator->memPool, 0, MAX_ORDER + 1); //забиваем пул нулями в количестве байт = MAX_ORDER + 1
	buddy_allocator->memPool[order] = buddy_allocator->memStart; // по самой большой степени кладем, memStart - это его начало, те изначальный размер блока
	return SUCCESS;
}

void * alloc(buddy_allocator_t *buddy_allocator, size_t size, uint8_t * order)
{
	node * ptr = buddyList;
	while (ptr != NULL && ptr->buddy_alloc != buddy_allocator) //как только дошли до нужного аллокатора или конца списка связности
	{
		ptr = ptr->next;
	}

	if (NULL == ptr) // если нашего аллокатора нет в списке
		return NULL;

	return alloc_buddy(buddy_allocator, size, order);
}

void * alloc_buddy(buddy_allocator_t *buddy_allocator, size_t size, uint8_t * order)
{
	uint8_t curr = 0;
	void * block = NULL;
	void * buddy = NULL;

	while (ORDERTOSIZE(curr) < size + 1) // нашли необходимую для данного размера степень 2
	{
		curr++;
	}

	if (curr < MIN_ORDER)  // переопределяем степень
	{
		*order = MIN_ORDER;
		curr = MIN_ORDER;
	}
	else
	{
		*order = curr;
	}

	while (curr <= buddy_allocator->maxOrder)
	{
		if (buddy_allocator->memPool[curr]) // если блок такого размера уже есть
			break;
		curr++;
	}

	if (curr > buddy_allocator->maxOrder) // хотим положить больше, чем вмещает аллокатор
	{
		printf("Memory allocation fail!!! No free memory available.\n");
		*order = 0;
		return NULL;
	}

	block = buddy_allocator->memPool[curr];
	buddy_allocator->memPool[curr] = *(void**)buddy_allocator->memPool[curr]; // в пуле по такому-то адресу лежит указатель на адрес памяти

	while (curr > *order) // делим наш блок на все степени от curr до order
	{
		curr--;
		buddy = findBuddy(buddy_allocator, block, curr);
		buddy_allocator->memPool[curr] = buddy;
	}

	return block;
	/*если в пуле не было подходящего блока, то надо вернуть наименьший подходящий,
	хоть мы его и делим на меньшие части, но нужен имеено указатель на начало блока, который начали делить*/
}

void buddy_allocator_free(buddy_allocator_t *buddy_allocator, void *ptr, uint8_t order) //ptr - адрес начала блока, который хотим освободить
{
	if (NULL == ptr)
		return;

	uint8_t curr = 0;
	void *  buddy = NULL;
	void ** memPtr = NULL;

	curr = order; // далее нужно найти какой блок начинается с этого адреса

	for (;; curr++)
	{
		buddy = findBuddy(buddy_allocator, ptr, curr);
		memPtr = &(buddy_allocator->memPool[curr]);

		while ((*memPtr != NULL) && (*memPtr != buddy))
			memPtr = (void **)*memPtr;

		if (*memPtr != buddy)
		{
			*(void**)ptr = buddy_allocator->memPool[curr];
			buddy_allocator->memPool[curr] = ptr;
			return;
		}
		ptr = (ptr < buddy) ? ptr : buddy;
		*memPtr = *(void**)*memPtr;
	}
}

void * findBuddy(buddy_allocator_t* buddyMem, void* block, uint8_t order)
{
	int offset = ((char*) block) - buddyMem->memStart;
	return (void *)((offset ^ (1 << order)) + ((char*)buddyMem->memStart));
}
