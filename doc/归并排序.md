### **归并排序**

归并排序是一种思想与快速排序相反的排序算法。快排优先考虑整个数组相对于某个基准数是有序的，然后再分别排序基准数两边的数组，范围由大到小。

而归并排序先从每两个数开始排序，然后将已经排序的数组范围看作一个数再进行排序。范围从小到大。

那么归并排序要考虑的问题有两个，一个是如何将两个已经排序的数组合并为一个有序的数组，另一个是边界的选取。

#### **将两个有序的数组合并为一个有序的数组**

答案是双指针法。所谓双指针即两个分别在两个数组上移动的下标变量，当数组1中的指针的数一直小于数组2指针的数时，数组1的指针就一直向下移动，直到数组2指针的数更小。

只是在归并排序中运用双指针法并不是两个数组，而是一个数组通过一个下标进行分割。

对于这种情况，双指针的简易做法是创建一个临时数组，将两个数组中的数写入其中，然后在复制到原数组。由于归并排序存在递归调用，所以临时数组应该动态创建，并及时释放。

#### **排序**

```c
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
```

