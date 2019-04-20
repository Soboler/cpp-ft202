#pragma once

#include "stdlib.h"
#include "stdint.h"

#define SUCCESS 1
#define FAIL    0

#define MIN_ORDER 4
#define MAX_ORDER 34
#define ORDERTOSIZE(i) (1 << (i)) /*макрос, возводим 2 в степень i */

struct buddy_allocator_t_
{
	size_t memSize; /* размер этого аллокатора*/
	uint8_t maxOrder; /* максимальная степень */
	void * memStart; /* старт пула */
	void * memPool[MAX_ORDER + 1]; /* аналог списка свободных блоков по степеням. по факту это пул */
};

typedef struct buddy_allocator_t_ buddy_allocator_t;

struct node_t /* наши подблоки, которые хотим аллоцировать */
{
	buddy_allocator_t * buddy_alloc;
	struct node_t * next;
};

typedef struct node_t node;

node  * buddyList; /* текущий лист блоков */

				   /**
				   * создаем аллокатор
				   * @param memory_size 
				   * @return новый аллокатор
				   */
buddy_allocator_t *constructor(size_t raw_memory_size);

/**
* уничтожаем аллокатор
* @param buddy_allocator
*/
void buddy_allocator_destroy(buddy_allocator_t *buddy_allocator);

/**
* аллоцируем 
* @param buddy_allocator 
* @param size размер памяти для аллокации
* @param order степень(нужна только для упрощения освобождения блока)
* @return указатель на аллоцированный блок, или @a NULL 
*/
void *alloc(buddy_allocator_t *buddy_allocator, size_t size, uint8_t * order);

/**
* Освобождвем блок .
* если @a ptr  @a NULL, ничего не делаем
* @param buddy_allocator 
* @param ptr память для деаллокации
* @param order степень
*/
void buddy_allocator_free(buddy_allocator_t *buddy_allocator, void *ptr, uint8_t order);

int initBuddyAlloc(buddy_allocator_t *buddy_allocator);
void * alloc_buddy(buddy_allocator_t *buddy_allocator, size_t size, uint8_t * order);
void * findBuddy(buddy_allocator_t * buddyMem, void * block, uint8_t order);
