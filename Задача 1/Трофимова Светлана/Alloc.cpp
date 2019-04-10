#include <iostream>

class Arr {
	size_t size_arr;
	int *arr;
	int last_index;

	public:
		Arr(size_t size_arr) {
			this->size_arr = size_arr;
			arr = (int*)malloc(this->size_arr);
			last_index = 0;
		}

		int get(size_t index) {
			if (index > last_index)
				throw std::range_error("wrong index");
			else
				return arr[index];
		}

		void set(size_t index, int value) {
			if (index * sizeof(int) >= size_arr)
				size_arr = 2 * (sizeof(int) * index);
				int *new_arr = (int*)malloc(size_arr);
				for (int i = 0; i <= last_index; i += 1) {
					new_arr[i] = arr[i];
				}
				free(arr);
				arr = new_arr;
				this->size_arr = size_arr;
			arr[index] = value;
			last_index = index;
		};

		void remove_all(size_t size_arr) {
			free(arr);
			this->size_arr = size_arr;
			last_index = 0;
			arr = (int*)malloc(this->size_arr);
		};
};