### **快速排序**

快速排序是一种效率为$O(N*logN)$的排序算法。

其基本思想为：

* 从数组中取出一个数作为基准数，将数组中比基准数小的移动到其左边，比基准数大的移动到其右边。
* 再对左右区间重复上一步，直到左右区间都只有一个数。

所以对于快速排序，其重点在于如何实现将第一步。

实现第一步的方法称为“挖坑填数法”。如果考虑选择数组中第0个数作为基准数，则将存储在另一个变量中，则数组中第0个位置相当于多了一个坑。

按照这一思想，要实现第一步就并不难了，实现代码为：

```c
int move_numbers(int arr[], int n) {
	int base = arr[0];
	int i = 0, j = n - 1;
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
}
```

需要注意的就是边界问题，相当于双指针的两个变量不断往中间靠拢时最终会停留在一个下标上，那个下标就是最终基准数的位置。

**快速排序**

通过递归调用`move_numbers`函数就可以迅速将数组排序，同样需要准确判断递归的出口条件。

将两步整合一下便可得下面的代码：

```c
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
```

对于分治排序算法，通常还可以通过多线程的方式进行优化。

但是，这种递归算法在数组规模十分庞大时空间复杂度非常高。