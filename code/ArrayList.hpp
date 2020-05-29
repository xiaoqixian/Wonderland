/*
 ArrayList: extends from List.hpp
 Achieve a elastic array with array
 */

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP
 
#include "List.hpp"
using namespace std;

template <typename T>
class ArrayList:public List {
	private:
		//int _length;
		//int _size;
		//T* _list;
		void expand();
	public:
		T* _list;
		int _length;
		int _size;
		ArrayList(int size);
		
		void insert(int index, T t);
		void add(T t);
		T get(int index);
		void set(int index, T t);
		void length();
		void remove(int index);
		T index(int index);
};

#endif
