/*
 merge sort
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void merge(int arr[], int divide, int n);
void sort(int arr[], int start, int end);

int main() {
	int arr[] = {1,4,23,56,2,6,22,78,90};
	sort(arr, 0, 9);
	PRINT_ARR(arr, 9);
	return 0;
}

void sort(int arr[], int start, int end) {
	if (start == end) {
		return ;
	}
	int mid = start + (end - start) / 2;
	sort(arr, start, mid);
	sort(arr, mid + 1, end);
	merge(arr, mid, end - start);
}

//divide is the start index of the second sorted part
void merge(int arr[], int divide, int n) {
	int* tmp = (int*)malloc(sizeof(arr));
	memset(tmp, 0, sizeof(arr));
	if (tmp == NULL) {
		printf("alloc memory failed\n");
		return ;
	}
	int i = 0, j = divide;
	int index = 0;
	while (i < divide && j < n) {
		if (arr[i] < arr[j]) {
			tmp[index++] = arr[i++];
		}
		else {
			tmp[index++] = arr[j++];
		}
	}
	while (i < divide) {
		printf("loop2\n");
		tmp[index++] = arr[i++];
	}
	while (j < n) {
		printf("loop3\n");
		tmp[index++] = arr[j++];
	}
	for (index = 0; index < n; index++) {
		arr[index] = tmp[index];
	}
	free(tmp);
}

