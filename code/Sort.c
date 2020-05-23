#include <stdio.h>
#include <stdlib.h>

void printArr(int nums[], int len);
void shellSort(int nums[], int len);
void mergeSort(int nums[], int len, int start);
void quickSort(int nums[], int start, int len);

int main() {
	char s[20];
	printf("%d\n", sizeof(s));
	return 0;
}

void printArr(int nums[], int len) {
	int i;
	printf("[");
	for (i = 0; i < len - 1; i++) {
		printf("%d, ",nums[i]);
	}
	printf("%d]", nums[len - 1]);
}

void shellSort(int nums[], int len) {
	int gap, i;
	for (gap = len / 2;gap > 0;gap = gap /2) {
		for (i = gap; i < len;i++) {
			int j = i;
			int curr = nums[i];
			while (j - gap >= 0 && curr < nums[j - gap]) {
				nums[j] = nums[j - gap];
				j = j - gap;
			}
			nums[j] = curr;
		}
	}
}

void mergeSort(int nums[], int len, int start) {
	if (len == 1) {
		printf("len = %d\n", len);
		return ;
	}
	else {
		printf("len = %d\n", len);
		int mid = (len >> 1) + start;
		mergeSort(nums, len / 2, start);
		mergeSort(nums, len / 2 + len % 2, mid);
		printf("len = %d\n", len);
		int i = start, j = mid, index = start;
		int arr[len];
		while (i < mid && j < len + start) {
			arr[index++] = nums[i] <= nums[j] ? nums[i++] : nums[j++];
		}
		while (i < mid) {
			arr[index++] = nums[i++];
		}
		while (j < len + start) {
			arr[index++] = nums[j++];
		}
		if (len == 10) {
			printf("index: %d\n", index);
		}
		for (i = start; i < len + start; i++) {
			nums[i] = arr[i];
		}
	}
}

void quickSort(int nums[],int start, int len) {
	if (len == 1) {
		return ;
	}
	int end = start + len, index = start + 1, i;
	for (i = index; i < end; i++) {
		if (nums[i] < nums[start]) {
			int tmp = nums[i];
			nums[i] = nums[index];
			nums[index] = tmp;
			index++;
		}
	}
	int tmp = nums[start];
	nums[start] = nums[index - 1];
	nums[index - 1] = tmp;
	if (index - 2 >= start) {
		quickSort(nums, start,  index - 1 - start);
	}
	if (index < end) {
		quickSort(nums, index, end - index);
	}
}
