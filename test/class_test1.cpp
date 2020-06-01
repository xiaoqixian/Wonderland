

#include <stdio.h>

template <typename T>
class List {
	public:
		virtual void print() = 0;
};

template <typename T>
class AList: public List<T> {
	public:
		void print();
};

int main() {
	return 0;
}
