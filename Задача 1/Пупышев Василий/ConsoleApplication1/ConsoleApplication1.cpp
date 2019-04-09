/*
Массив с динамическим расширением и основными функциями
*/



#include <iostream>
#include <cstddef>
#include "Source1.cpp"
template <typename T>

class List {
public:
	explicit List(size_t size = 0, const T& value = T()) : csize_(size), size_(size * 2) {
		data_ = new T[size_];
		for (size_t i = 0; i < size_; i++) {
			data_[i] = value;
		}
	}

	~List() {
		delete[]  data_;
	}

	size_t  size() const {
		return  csize_;
	}

	T  operator [](size_t i) const {
		return  data_[i];
	}

	T& operator [](size_t i) {
		return  data_[i];
	}

	List& operator=(List const& t) {
		if (this != &t) {
			size_ = t.size_;
			delete[] data_;
			data_ = new T[size_];
			for (size_t i = 0; i < size_; i++) {
				data_[i] = t.data_[i];
			}
		}
	}

	List(List const& t) {
		size_ = t.size_;
		delete [] data_;
		data_ = new T[size_];
		for (size_t i = 0; i < size_; i++) {
			data_[i] = t.data_[i];
		}
	}

	void add(T ni) {
		if (size_ - 1 == csize_) {
			size_ = size_ * 2;
			T* data_tmp = new T[size_];
			for (int i = 0; i < csize_; i++) {
				data_tmp[i] = data_[i];
			}
			data_tmp[csize_] = ni;
			delete[] data_;
			data_ = data_tmp;
		}
		else {
			data_[csize_] = ni;
		}
		csize_++;
	}

	void del(T item) {
		T* data_tmp = new T[size_];
		int delta = 0;
		bool bol = true;
		int d = csize_;
		for (int i = 0; i < d; i++) {
			if (item == data_[i] && bol) {
				delta = 1;
				bol = false;
				csize_--;
				continue;
			}
			data_tmp[i - delta] = data_[i];
		}
		delete[] data_;
		data_ = data_tmp;
	}

	void delall(T item) {
		T* data_tmp = new T[size_];
		int delta = 0;
		int d = csize_;
		for (int i = 0; i < d; i++) {
			if (item == data_[i]) {
				delta++;
				csize_--;
				continue;
			}
			data_tmp[i - delta] = data_[i];
		}
		delete[] data_;
		data_ = data_tmp;
	}

	void insert(int index, T item) {
		if (index < 0 || index >= csize_) {
			throw "index out of the range";
		}
		else {
			T* data_tmp = new T[size_];
			int b = csize_;
			int delta = 0;
			for (int i = 0; i < b; i++) {
				if (index == i) {
					data_tmp[i] = item;
					delta++;
					csize_++;
				}
				data_tmp[i + delta] = data_[i];
			}
			delete[] data_;
			data_ = data_tmp;
		}
	}

	void clean() {
		delete[] data_;
		T* data_ = new T[4];
		csize_ = 0;
		size_ = 4;
	}

private:
	size_t   size_;
	size_t csize_;
	T* data_;
};

int main()
{
	List<int> lst = List<int>(2, 5);
	std::cout << lst[2] << std::endl;
	for (int i = 0; i < 5; i++) {
		lst.add(i);
	}
	for (int i = 0; i < lst.size(); i++)
		std::cout << lst[i] << "  ";
	lst.delall(5);
	lst.del(0);
	std::cout << std::endl;
	for (int i = 0; i < lst.size(); i++)
		std::cout << lst[i] << "  ";
	std::cout << std::endl;
	lst.insert(2, 77);
	for (int i = 0; i < lst.size(); i++)
		std::cout << lst[i] << "  ";
	lst.clean();
	lst.add(4);
	std::cout << std::endl;
	for (int i = 0; i < lst.size(); i++)
		std::cout << lst[i] << "  ";
	std::cout << "\nhello";
	//------------------------------------------
	LinkedList<int> lst1 = LinkedList<int>();
	for (int i = 0; i < 5; i++)
		lst1.add(i);
	std::cout <<"\n" << lst1.size() << "\n";
	for (int i = 0; i < lst1.size(); i++) {
		std::cout << i << "\n";
		std::cout << lst1[i] << "  ";
	}
}