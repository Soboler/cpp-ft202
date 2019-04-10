#include <iostream>

class Stack {
	size_t size_arr;
	int *arr;
	int last_index;

public:
	Stack(size_t size_arr) {
		this->size_arr = size_arr;
		arr = (int*)malloc(this->size_arr);
		last_index = -1;
	}

	int pop_back() {
		if (last_index == -1)
			throw std::range_error("stack empty");
		else
			last_index--;
			return arr[last_index + 1];
	}

	int pop() {
		if (last_index == -1)
			throw std::range_error("stack empty");
		return arr[last_index];
	}

	void push_back(int value) {
		if ((last_index + 1) * sizeof(int) >= size_arr)
			size_arr = 2 * this->size_arr;
			int *new_arr = (int*)malloc(size_arr);
			for (int i = 0; i <= last_index; i += 1) {
				new_arr[i] = arr[i];
			}
			free(arr);
			arr = new_arr;
			this->size_arr = size_arr;
		arr[last_index + 1] = value;
		last_index++;
	};

	void remove_all(size_t size_arr) {
		free(arr);
		this->size_arr = size_arr;
		last_index = -1;
		arr = (int*)malloc(this->size_arr);
	};
};