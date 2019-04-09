#pragma once

template <class TElement> class element
{
public:
	element* next_element;
	element* prev_element;
	TElement* value;
	element(element* _next_element, element* _prev_element, TElement* _value)
	{
		next_element = _next_element;
		prev_element = _prev_element;
		value = _value;
	}
};

//Связный список
template <class TElement> class linked_list
{
private:
	element<TElement>* head;
	element<TElement>* tail;
	int elements_count;
	size_t size;

public:
	linked_list()
	{
		head = NULL;
		size = 0;
		elements_count = 0;
	}

	void push_back(TElement* value)
	{
		if (head == nullptr)
		{
			head = new element<TElement>(nullptr, nullptr, value);
			tail = head;
		}
		else
		{
			if (tail->value == nullptr)
			{
				tail->value = value;
			}
			else
			{
				tail->next_element = new element<TElement>(nullptr, tail, value);
				tail = tail->next_element;
			}
		}
		size += sizeof(value);
		elements_count++;
	}

	TElement pop_back()
	{
		auto result = tail->value;
		tail = tail->prev_element;
		tail->next_element = nullptr;
		return result;
	}

	void set(int index, TElement* value_to_add)
	{
		auto element = head;
		bool index_found = false;
		for (int i = 0; i < elements_count; i++)
		{
			if (i == index)
			{
				element->value = value_to_add;
				index_found = true;
				break;
			}
			element = element->next_element;
		}
		if (!index_found)
		{
			throw std::exception("There is no such index in Linear!");
		}
	}

	TElement get(int index)
	{
		auto element = head;
		bool index_found = false;
		for (int i = 0; i < elements_count; i++)
		{
			if (i == index)
			{
				return *element->value;
			}
			element = element->next_element;
		}
		throw std::exception("There is no such index in Linear!");
	}

	void remove_all()
	{
		head = NULL;
		tail = NULL;
		size = 0;
		elements_count = 0;
	}
};