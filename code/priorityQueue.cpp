/*
 priority queue
 队列是一个不值得怎么研究的数据结构, 但是优先队列不是. 
 */
 
#include <stdio.h>

typedef int (*pq_comparator_ptr)(void* i, void* j);

typedef struct pq_node_s {
	int pri;//priority value
	void* content;
} pq_node;

typedef struct pq_s {
	int size;
	pq_node** queue;//the node queue
	pq_comparator_ptr comparator;
} pq_t;

class PriorityQueue {
	private:
		int size;
		pq_node** queue;
		pq_comparator_ptr comparator;
		
	public:
		PriorityQueue() {
			this->size = 0;
			this->queue = NULL;
			this->comparator = NULL;
		}
		
		PriorityQueue(pq_comparator_ptr comparator) {
			size = 0;
			queue = NULL;
			this->comparator = comparator;
		}
		
		void setComparator(pq_comparator_ptr comparator) {
			this->comparator = comparator;
		}
		
		
};

int pq_init(pq_t* pq) {
	if (pq != NULL) {
		return 0;
	}
	pq = (pq_t*)malloc(sizeof(pq_t));
	if (pq == NULL) {
		printf("allocate memory to pq failed\n");
		return -1;
	}
	
	pq->comparator = NULL;
	pq->size = 0;
	pq->queue = NULL;
	return 0;
}

int empty(pq_t* pq) {
	
}
