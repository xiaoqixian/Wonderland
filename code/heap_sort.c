/*
 heap sort
*/

#include <stdio.h>

//交换元素 
inline void swap(int arr[], int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

//构造堆 
void heapify(int arr[], int n, int i) {
	if (i >= n) {
		return ;
	}
	int max = i;
	int left = 2 * i + 1, right = 2 * i + 2;
	if (left < n && arr[max] < arr[left]) {
		max = left;
	}
	if (right < n && arr[max] < arr[right]) {
		max = right;
	}
	if (max != i) {
		swap(arr, max, i);
		heapify(arr, n, max);
	}
}

void build_heap(int arr[], int n) {
	int last_node = n - 1;
	int parent = (last_node - 1) / 2;
	int i;
	for (i = parent; i >= 0; i--) {
		heapify(arr, n, i);
	}
}

void heap_sort(int arr[], int n) {
	build_heap(arr, n);
	int i;
	for (i = n - 1; i >= 0; i--) {
		swap(arr, 0, i);
		heapify(arr, i, 0);
	}
}

void print_arr(int arr[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
	int arr[] = {4,8,3,1,5,9,2,0};
	heap_sort(arr, 8);
	print_arr(arr, 8);
	return 0;
}
