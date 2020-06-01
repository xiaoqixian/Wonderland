/*
 ArrayList: extends from List.hpp
 Achieve a elastic array with array
 */

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP
 
#include "List.hpp"
using namespace std;

template <typename T>
class ArrayList:public List<T> {
	private:
		int _length;
		int _size;
		T* _list;
		void expand();
	public:
		//ArrayList();
		ArrayList(int size);
		
		void insert(int index, T t);
		void add(T t);
		T get(int index);
		void set(int index, T t);
		int length();
		void remove(int index);
		int index(T t);
		void print(void*);
		void print(void (*printFunc)(void*));
};

#endif
