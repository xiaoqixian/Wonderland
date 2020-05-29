/*
 List header file
 Child Class: ArrayList, LinkedList
 List�������Ϊ������, �亯�����������Ϊ���麯��, �����ArrayList��LinkedList������ʵ����Щ���麯�� 
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
