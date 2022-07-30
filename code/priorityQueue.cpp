/*
 priority queue
 队列是一个不值得怎么研究的数据结构, 但是优先队列不是. 
 优先队列有非常多的应用场景，比如操作系统内部，比如服务器对于客户端需求的处理。
 所以研究清楚是非常必要的。 
 */
 
/*
 本优先队列参考《算法导论》中的实现，通过堆排序算法的原理进行优先队列的整理。 
 我在第一次碰到这种优先队列的写法时还没有将其与堆排序联系起来，导致看的过程很困难，现在想来就是十分后悔。 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*pq_comparator_ptr)(void* i, void* j);

typedef struct pq_node_s {
	int pri;//priority value
	void* content;
} pq_node;

typedef struct pq_s {
	int size;
	int alloc;
	pq_node** queue;//the node queue
	pq_comparator_ptr comparator;
} pq_t;

void exch(pq_t* pq, size_t i, size_t j) {
    pq_node* tmp = pq->queue[i];
    pq->queue[i] = pq->queue[j];
    pq->queue[j] = tmp;
}

/* swim相当于堆排序里面的heapify操作。
   对于一个数组，将其“投射”到一棵完全二叉树上的话， 对于数组中索引为k的节点，其父节点在数组中的索引为k/2.
   所以这个函数可以保证完全二叉树的节点k所有的这条从根节点到叶节点的路径上的所有节点都是有序的。从而保证完
   全二叉树的层与层之间都是有序的，如：如果是小顶堆的话，则上一层的节点都会小于下一层的节点。 
 */
void swim(pq_t* pq, size_t k) {
    while (k > 0 && pq->comparator(pq->queue[k], pq->queue[k/2])) {
        exch(pq, k, k/2);
        k /= 2;
    }
}

/*
 swim操作只能适用于在完全二叉树的最底层的最右边加入节点。当堆的某个位置插入一个节点时就可能使堆失衡，这时候就需要
 用到sink函数。 
 基本操作即对于索引k处的节点，先与较小的子节点进行交换操作，然后节点k被换到了原来较小节点的位置。于是又来到2k+1或2k+2
 的位置进行sink操作。
 这样就能使得k节点以下的子树是符合堆的。
 
 你可能会问swim操作已经可以保证堆是不会失衡的，为什么还要sink函数呢？ 
 在删除队列中的优先级最高即位于数组0处的节点时，为了效率起见，将0处的节点与最后一个节点交换顺序。这样就可以直接删除
 最后一个节点就好了。但0处相当于空降了一个节点，这时就需要进行sink操作。 
 */
size_t sink(pq_t* pq, size_t k) {
    size_t j;
    size_t nalloc = pq->alloc;
    
    while (2*k <= nalloc) {
        j = 2*k + 1; 
        if (j < nalloc - 1 && pq->comparator(pq->queue[j+1], pq->queue[j])) j++;
        if (!pq->comparator(pq->queue[j], pq->queue[k])) break;
        exch(pq, j, k);
        k = j;
    }
    return k;
}

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
	pq->size = 4;
	pq->alloc = 0;
	pq->queue = NULL;
	return 0;
}

int pq_init(pq_t* pq, int size) {
	if (pq != NULL) {
		return 0;
	}
	if (size <= 0) {
		printf("size has to be positive number!\n");
		return -1;
	}
	pq = (pq_t*)malloc(sizeof(pq_t));
	if (pq == NULL) {
		printf("allocate memory to pq failed\n");
		return -1;
	}
	
	pq->comparator = NULL;
	pq->size = size;
	pq->alloc = 0;
	pq->queue = NULL;
	return 0;
}

int pq_expand(pq_t* pq) {
	//如果已分配数量小于当前空间的一半，则不进行扩容 
	if (pq->alloc < (pq->size >> 1)) {
		return 0;
	}
	pq_node** new_pq = (pq_node**)malloc(pq->size << 1);
	if (new_pq == NULL) {
		printf("allocate memory to new priority queue failed\n");
		return -1;
	}
	memset(new_pq, 0, sizeof(new_pq));
	memcpy(pq->queue, new_pq, pq->alloc*sizeof(pq_node*));
	free(pq->queue);
	pq->queue = new_pq;
	pq->size <<= 1;
	return 0;
}

void pq_add(pq_t* pq, void* cont, int pri) {
	if (pq->alloc >= pq->size) {
		if (pq_expand(pq) < 0) {
			return ;
		}
	}
	pq_node* node = (pq_node*)malloc(sizeof(pq_node));
	node->pri = pri;
	node->content = cont;
	pq->queue[pq->alloc++] = node;
	swim(pq, pq->alloc - 1);
}

int empty(pq_t* pq) {
	return pq->alloc == 0? 1:0;
}

void pq_del_first(pq_t* pq) {
	if (pq->alloc <= 0) {
		return ;
	}
	exch(pq, 0, pq->alloc - 1);
	pq->alloc--;
	sink(pq, 0);
}

int main() {
	return 0;
}
