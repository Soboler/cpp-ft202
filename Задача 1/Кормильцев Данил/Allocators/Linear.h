#pragma once

template <class TElement> class linear
{
private:
	TElement* memory;
	size_t total_size;
	size_t element_size;
	uint32_t count;

	void increase_size()
	{
		total_size = total_size * 2;
		auto new_memory = (TElement*)malloc(total_size);
		for (uint32_t i = 0; i < count; i++)
		{
			new_memory[i] = memory[i];
		}
		memory = new_memory;
	}

public:
	explicit linear()
	{
		element_size = sizeof(TElement);
		total_size = element_size;
		memory = (TElement*)malloc(total_size);
		count = 0;
	}

	void push_back(TElement value_to_add)
	{
		if ((count + 1) * element_size > total_size)
		{
			increase_size();
		}
		memory[count] = value_to_add;
		count++;
	}

	TElement pop_back()
	{
		if (count == 0)
		{
			throw std::exception("The linear is empty");
		}
		count--;
		return memory[count];
	}

	void set(int index, TElement value_to_add)
	{
		if (index < 0 || index > count)
		{
			throw std::exception("There is no such index in linear!");
		}
		memory[index] = value_to_add;
	}

	TElement get(int index)
	{
		if (index < 0 || index > count)
		{
			throw std::exception("There is no such index in linear!");
		}
		return memory[index];
	}

	void remove_all()
	{
		count = 0;
	}
};

