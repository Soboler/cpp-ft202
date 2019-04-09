#pragma once

template <class TElement> class stack
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
	explicit stack()
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
			throw std::exception("The Linear is empty");
		}
		count--;
		return memory[count];
	}

	void remove_all()
	{
		count = 0;
	}
};
