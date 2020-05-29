/*
 ArrayList source file
 */
 
#include "ArrayList.hpp"
#include <string.h>
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
	memcpy(new_list, this->_list, sizeof(this->_length);
	delete[] _list;
	this->_list = new_list;
	this->_size <<= 1;
}

template <typename T>
void ArrayList<T>::add(T t) {
	if (_length >= _size) {
		expand();
	}
	_array[_length++] = t;
}

template <typename T>
void ArrayList<T>::insert(int index, T t) {
	if (_length > _size) {
		expand();
	}
	if (index < 0 || index > _length) {
		printf("not allowed to insert an element outside the list\n");
		return ;
	}
	int i;
	for (i = _length; i > index; i--) {
		_list[i] = _list[i - 1];
	}
	_list[index] = t;
	_length++;
}

int main() {
	return 0;
}

