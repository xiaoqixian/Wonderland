### **排序算法**

冒泡排序、选择排序和插入排序较为简单理解，不讲

动图来源网络，侵删

---

#### **4. 希尔排序（Shell Sort）**

![](https://images2018.cnblogs.com/blog/849589/201803/849589-20180331170017421-364506073.gif)

代码：

```c
void ShellSort(int nums[], int len) {
	int gap;
	for (gap = len / 2; gap > 0; gap /= 2) {
		for (i = gap; i < len; i++) {
			int j = i;
			int curr = nums[i];
			while (j - gap >= 0 && nums[j - gap] > nums[j]) {
				nums[j] = nums[j - gap];
				j -= gap;
			}
			nums[j] = curr;
		}
	}
}
```

希尔排序的核心在于将数组分成多个组，每个组之间的元素index之差为一个gap，然后在组内将序拍好，再不断将gap缩小使得组内元素越来越多，最后达到总体的有序。这其实是一种分治的思想。

#### **5. 归并排序（Merge Sort）**

![](https://images2017.cnblogs.com/blog/849589/201710/849589-20171015230557043-37375010.gif)

某种程度上，归并排序可以看做希尔排序的逆过程。

#### **6. 快速排序**

```c
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
```

快速排序的核心在于在数组中寻找一个数，然后移动数组中的值使得数组中小于该数的数全在该数的左边，大于该数的数在该数的右边。

然后利用递归继续对该数两边的子数组进行排序。