#ifndef ARRAY_H_
#define ARRAY_H_

#include <iostream>
#include <algorithm>
#include <typeinfo>

template <typename T>
class Array {
public:
	enum Mode {
		Immutable = 0x01,
		Mutable = 0x02
	};
	Array(Mode _Mode = Array::Mode::Mutable, size_t _Size = 1) {
		max_size = _Size;
		mode = _Mode;

		_size = 0;
		arr = new T[max_size];

		for (size_t i(0); i < max_size; i++)
			arr[i] = NULL;
	}

	~Array() {
		delete[] arr;
	}

	T operator[](int index) {
		if (index < max_size)
			return arr[index];
		else
		{
			return NULL;
		}
	}

	T at(int index) {
		if (index < max_size)
			return arr[index];
		else
		{
			//std::cerr << "Index is out of array!" << std::endl;
			return NULL;
		}
	}

	size_t size() {
		return _size;
	}

	size_t length() {
		return max_size;
	}

	bool append(const T value) {
		if (mode == Mode::Mutable)
		{
			if (_size == max_size)
			{
				T* tmp = new T[max_size += 1];
				for (size_t i = 0; i < _size; i++)
					tmp[i] = arr[i];
				delete[] arr;
				arr = tmp;
			}
			arr[_size] = value;
			_size++;
			return true;
		}
		else if (mode == Mode::Immutable && _size < max_size)
		{
			arr[_size] = value;
			_size++;
			return true;
		}
		else
			return false;
	}

	void pop() {
		if (_size > 0)
		{
			arr[_size-1] = NULL;
			_size--;
			max_size--;
			T* tmp = new T[max_size];
			for (size_t i = 0; i < _size; i++)
				tmp[i] = arr[i];
			delete[] arr;
			arr = tmp;
		}
	}

	bool remove(int index) {
		if (index >= max_size)
			return false;
		arr[index] = NULL;
		T* tmp = new T[max_size];
		for (size_t i(0), j(0); i < _size; i++, j++)
		{
			if (j == index)
			{
				if (j < _size - 1)
				{
					j++;
					tmp[i] = arr[j];
					j--;
				}
				else
					tmp[i] = arr[j];
			}
			else
				tmp[i] = arr[j];
		}
		delete[] arr;
		max_size--;
		_size--;
		T *tmp2 = new T[max_size];
		for (size_t i(0); i < _size; i++)
			tmp2[i] = tmp[i];
		delete[] tmp;
		arr = tmp2;
		return true;
	}

	bool remove(int F_Index, int S_Index) {
		if (std::max(F_Index, S_Index) >= max_size || F_Index >= S_Index || std::min(F_Index, S_Index) < 0)
			return false;
		for (size_t i(F_Index); i < S_Index; i++)
			arr[i] = NULL;

		T *tmp = new T[max_size];
		for (size_t i(0), j(0); i < _size; j++)
		{
			if (j >= F_Index && j <= S_Index)
				j++;
			else
			{
				tmp[i] = arr[j];
				i++;
			}
		}
		delete[] arr;
		max_size -= (S_Index - F_Index) + 1;
		_size -= (S_Index - F_Index) + 1;
		T *tmp2 = new T[max_size];
		for (size_t i(0); i < _size; i++)
			tmp2[i] = tmp[i];
		delete[] tmp;
		arr = tmp2;
		return true;
	}

	bool removeAll() {
		if (_size == 0)
			return false;
		for (size_t i(0); i < _size; i++)
			arr[i] = NULL;
		_size = 0;
		max_size = 0;
		delete[] arr;
		arr = new T[max_size += 1];
	}

	bool isEmpty() {
		return _size == 0;
	}

	bool resize(const int newSize) {
		if (newSize > _size)
		{
			if (_size == 0)
			{
				delete[] arr;
				max_size = newSize;
				arr = new T[max_size];
			}
			else
			{
				T *tmp = new T[newSize];
				for (size_t i(0); i < newSize; i++)
					tmp[i] = NULL;
				for (size_t i(0); i < _size; i++)
					tmp[i] = arr[i];
				delete[] arr;
				max_size = newSize;
				arr = tmp;
			}
			return true;
		}
		else
			return false;
	}

	bool push_back(const T value) {
		return append(value);
	}

	bool push_front(const T value) {
		if (mode == Mode::Mutable)
		{
			T *tmp = new T[_size == max_size ? max_size += 1 : max_size];
			for (size_t i(1), j(0); j < _size; i++, j++)
				tmp[i] = arr[j];
			tmp[0] = value;
			_size++;
			delete[] arr;
			arr = tmp;
			return true;
		}
		else if (mode == Mode::Immutable && _size < max_size)
		{
			T *tmp = new T[max_size];
			for (size_t i(1), j(0); j < _size; i++, j++)
				tmp[i] = arr[j];
			tmp[0] = value;
			_size++;
			delete[] arr;
			arr = tmp;
			return true;
		}
		else
			return false;
	}

	T &front() {
		return arr[0];
	}

	T &back() {
		return arr[_size-1];
	}

	bool insert(int index, const T value) {
		if (index < 0)
			return false;
		switch (mode)
		{
		case Mode::Mutable:
			if (_size == max_size)
			{
				T *tmp = new T[max_size += 1];
				for (size_t i = 0; i < _size; i++)
					tmp[i] = arr[i];
				delete[] arr;
				arr = tmp;
			}
			T *tmp = new T[max_size];
			_size++;
			for (size_t i(0), j(0); j < _size; i++, j++)
			{
				if (i == index)
				{
					tmp[i] = value;
					j--;
				}
				else
					tmp[i] = arr[j];
			}
			delete[] arr;
			arr = tmp;
			return true;
			break;
		}
	}

	int find_first(const T value) {
		for (size_t i(0); i < _size; i++)
		{
			if (arr[i] == value)
			{
				return i;
			}
		}
	}

	int find_last(const T value) {
		for (size_t i(_size - 1); i >= 0; i--)
		{
			if (arr[i] == value)
			{
				return i;
			}
		}
	}

	bool contains(const T value) {
		for (size_t i(0); i < _size; i++)
		{
			if (arr[i] == value)
				return true;
		}
		return false;
	}

	Mode getMode() const {
		return mode;
	}

	void clear() {
		removeAll();
	}

	Array<T> &operator=(Array<T> array) {
		//if (mode != array.getMode())
		//	return NULL;
		delete[] arr;
		arr = new T[array.size()];
		for (size_t i(0); i < array.size(); i++)
			arr[i] = array[i];
		_size = array.size();
		max_size = array.size();
		return *this;
	}

	bool operator==(Array<T> array) {
		if (_size != array.size())
			return false;

		Array<T> temp1;
		for (size_t i(0); i < array.size(); i++)
			temp1.push_back(array[i]);
		Array<T> temp2;
		for (size_t i(0); i < _size; i++)
			temp2.append(arr[i]);

		int count = 0;

		temp1.sortDigits();
		temp2.sortDigits();

		for (size_t i(0); i < temp1.size(); i++)
		{
			if (temp1[i] == temp2[i])
				count++;
		}

		if (count == temp1.size())
			return true;
		else
			return false;
	}

	void sortDigits() {
			Array<T> temp;
			Array<T> temp2;
			int max = 0;
			int id = 0;
			int count = 0;
			for (size_t i(0); i < _size; i++)
				temp.append(arr[i]);

			while (true)
			{
				if (temp.size() == 0)
					break;

				for (size_t i(0); i < temp.size(); i++)
				{
					if (max <= temp[i])
					{
						max = temp[i];
						id = i;
					}
				}

				//std::cout << max << std::endl;

				temp2.append(max);
				temp.remove(id);
				max = 0;
				id = 0;
			}
			removeAll();

			T *tmp = new T[temp2.size()];
			for (size_t i(0); i < temp2.size(); i++)
				tmp[i] = temp2[i];

			//temp2.printDebug();
			//std::cout << "------------------------------------\n";

			delete[] arr;
			arr = tmp;

			temp.clear();
			temp2.clear();
	}

	void printDebug() {
		for (size_t i(0); i < _size; i++)
			std::cout << "Array[" << i << "] = " << arr[i] << std::endl;
	}

	void print() {
		for (size_t i(0); i < _size; i++)
			std::cout << arr[i] << std::endl;
	}


	class Iterator;

	Iterator begin() {
		return arr;
	}
	Iterator end() {
		return arr + _size;
	}
	
private:
	int _size;
	size_t max_size;
	T *arr;
	Mode mode;
	

	class Iterator {
	public:
		Iterator(T *first) {
			current = first;
		}

		T &operator+(int n) {
			return *(current + n);
		}
		T &operator-(int n) {
			return *(current - n);
		}
		T &operator++(int) {
			return *current++;
		}
		T &operator--(int) {
			return *current--;
		}
		T &operator++() {
			return *++current;
		}
		T &operator--() {
			return *--current;
		}
		Iterator &operator+=(std::ptrdiff_t n) {
			current = current + n;
			return *this;
		}
		Iterator &operator-=(std::ptrdiff_t n) {
			current = current - n;
			return *this;
		}
		Iterator &operator-(Iterator &it) {
			this->current -= *it.current;
			return *this;
		}
		Iterator &operator+(Iterator &it) {
			this->current += it.current;
			return *this;
		}

		bool operator==(const Iterator &it) {
			return current == it.current;
		}
		bool operator!=(const Iterator &it) {
			return current != it.current;
		}
		T &operator*() {
			return *current;
		}
	private:
		T *current;
	};
};

#endif // ARRAY_H_