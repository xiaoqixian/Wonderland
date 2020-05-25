/*
  quick sort
 */
 
#include <stdio.h>
#include "common.h"

//start表示分段数组的开始下标，end表示结束下标 
int move_numbers(int arr[],int start, int end) {
	int base = arr[start];
	int i = 0, j = end;
	while (i < j) {
		while (i < j && arr[j] >= base) {
			j--;
		}
		if (i < j) {
			arr[i++] = arr[j];
		}
		//PRINT_ARR(arr, 7);
		while (i < j && arr[i] < base) {
			i++;
		}
		if (i < j) {
			arr[j--] = arr[i];
		}
		//PRINT_ARR(arr, 7);
	}
	arr[i] = base;
	return i;
}

void quick_sort(int arr[], int start, int end) {
	if (start < end) {
		int base = arr[start];
		int i = start, j = end;
		while (i < j) {
			while (i < j && arr[j] >= base) {
				j--;
			}
			if (i < j) {
				arr[i++] = arr[j];
			}
			while (i < j && arr[i] < base) {
				i++;
			}
			if (i < j) {
				arr[j--] = arr[i];
			}
		}
		arr[i] = base;
		quick_sort(arr, start, i - 1);
		quick_sort(arr, i + 1, end);
	}
}

int main() {
	int arr[] = {5,1,8,9,2,3,0};
	quick_sort(arr, 0, 6);
	PRINT_ARR(arr, 7);
	return 0;
}
