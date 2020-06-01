/*
 priority queue
 ������һ����ֵ����ô�о������ݽṹ, �������ȶ��в���. 
 ���ȶ����зǳ����Ӧ�ó������������ϵͳ�ڲ���������������ڿͻ�������Ĵ���
 �����о�����Ƿǳ���Ҫ�ġ� 
 */
 
/*
 �����ȶ��вο����㷨���ۡ��е�ʵ�֣�ͨ���������㷨��ԭ��������ȶ��е����� 
 ���ڵ�һ�������������ȶ��е�д��ʱ��û�н������������ϵ���������¿��Ĺ��̺����ѣ�������������ʮ�ֺ�ڡ� 
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

/* swim�൱�ڶ����������heapify������
   ����һ�����飬���䡰Ͷ�䡱��һ����ȫ�������ϵĻ��� ��������������Ϊk�Ľڵ㣬�丸�ڵ��������е�����Ϊk/2.
   ��������������Ա�֤��ȫ�������Ľڵ�k���е������Ӹ��ڵ㵽Ҷ�ڵ��·���ϵ����нڵ㶼������ġ��Ӷ���֤��
   ȫ�������Ĳ����֮�䶼������ģ��磺�����С���ѵĻ�������һ��Ľڵ㶼��С����һ��Ľڵ㡣 
 */
void swim(pq_t* pq, size_t k) {
    while (k > 0 && pq->comparator(pq->queue[k], pq->queue[k/2])) {
        exch(pq, k, k/2);
        k /= 2;
    }
}

/*
 swim����ֻ������������ȫ����������ײ�����ұ߼���ڵ㡣���ѵ�ĳ��λ�ò���һ���ڵ�ʱ�Ϳ���ʹ��ʧ�⣬��ʱ�����Ҫ
 �õ�sink������ 
 ������������������k���Ľڵ㣬�����С���ӽڵ���н���������Ȼ��ڵ�k��������ԭ����С�ڵ��λ�á�����������2k+1��2k+2
 ��λ�ý���sink������
 ��������ʹ��k�ڵ����µ������Ƿ��϶ѵġ�
 
 ����ܻ���swim�����Ѿ����Ա�֤���ǲ���ʧ��ģ�Ϊʲô��Ҫsink�����أ� 
 ��ɾ�������е����ȼ���߼�λ������0���Ľڵ�ʱ��Ϊ��Ч���������0���Ľڵ������һ���ڵ㽻��˳�������Ϳ���ֱ��ɾ��
 ���һ���ڵ�ͺ��ˡ���0���൱�ڿս���һ���ڵ㣬��ʱ����Ҫ����sink������ 
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
	//����ѷ�������С�ڵ�ǰ�ռ��һ�룬�򲻽������� 
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
