/*
 ArrayList source file
 */
 
#include "ArrayList.hpp"
#include <string.h>
#include <stdio.h>
using namespace std;

template <typename T>
ArrayList<T>::ArrayList(int size) {
	this->_size = size;
	this->_list = new T[size];
	this->_length = 0;
}

template <typename T>
void ArrayList<T>::expand() {
	if (this->_size > (this->_length << 1)) { //如果还有一半以上的空余空间就不进行扩容 
		return ;
	}
	T* new_list = new T[this->_size << 1];
	if (new_list == NULL) {
		//printf("allocate memory to new list failed\n");
		//exit(0);
	}
	memset(new_list, 0, sizeof(new_list));
	memcpy(new_list, this->_list, this->_length * sizeof(T));
	delete[] this->_list;
	this->_list = new_list;
	this->_size <<= 1;
}

template <typename T>
void ArrayList<T>::add(T t) {
	if (this->_length >= this->_size) {
		expand();
	}
	this->_list[this->_length++] = t;
}

template <typename T>
void ArrayList<T>::insert(int index, T t) {
	if (this->_length > this->_size) {
		expand();
	}
	if (index < 0 || index > this->_length) {
		printf("not allowed to insert an element outside the list\n");
		return ;
	}
	int i;
	for (i = this->_length; i > index; i--) {
		this->_list[i] = this->_list[i - 1];
	}
	this->_list[index] = t;
	this->_length++;
}

template <typename T>
void ArrayList<T>::set(int index, T t) {
	if (index >= _length || index < 0) {
		printf("index is greater than the array size\n");
		return ;
	}
	_list[index] = t;
}

template <typename T>
T ArrayList<T>::get(int index) {
	if (index >= _length || index < 0) {
		printf("index is greater than the array size\n");
		return 0;
	}
	return _list[index];
}

template <typename T>
int ArrayList<T>::length() {
	return _length;
}

template <typename T>
void ArrayList<T>::remove(int index) {
	if (index >= _length || index < 0) {
		printf("index is greater than the array size\n");
		return ;
	}
	int i;
	for (i = index; i < _length; i++) {
		_list[i] = _list[i + 1];
	}
	_length--;
}

template <typename T>
int ArrayList<T>::index(T t) {
	return 0;
}

template <typename T>
void ArrayList<T>::print(void (*printFunc)(void*)) {
	int i;
	for (i = 0; i < this->_length; i++) {
		(*printFunc)(&this->_list[i]);
	}
	printf("\n");
}

typedef void (*print_func)(void* i);

void print_int(void* i) {
	printf("%d ", *((int*)i));
}

int main() {
	ArrayList<int> array(4);
	array.add(1);
	array.insert(0, 3);
	array.add(2);
	print_func pf = print_int;
	array.print(pf);
	array.set(2, 10);
	array.print(pf);
	printf("size = %d\n", array.length());
	return 0;
}

