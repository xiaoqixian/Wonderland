/*
 List header file
 Child Class: ArrayList, LinkedList
 List将被设计为抽象类, 其函数都将被设计为纯虚函数, 后面的ArrayList和LinkedList都必须实现这些纯虚函数 
 */
 
#ifndef LIST_HPP
#define LIST_HPP
using namespace std;

template <typename T>
class List {
	public:
		virtual void insert(int index, T t) = 0; 
		virtual void add(T t) = 0;
		virtual T get(int index) = 0;
		virtual void set(int index, T t) = 0;
		virtual int length() = 0;
		virtual void remove(int index) = 0;
		virtual int index(T t) = 0;
};

#endif
