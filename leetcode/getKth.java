/*
 * Leetcode 1387.将整数按权重排序
 * 刚才看到一个牛逼的Java的代码，直接利用快速排序对键值对进行排序。
 * 时间达到了25ms.
 * 
 */

class Solution {

    public int getKth(int lo, int hi, int k) {
        int[][] nums = new int[hi - lo + 1][2];
        for (int i = lo; i <= hi; ++i) {
            nums[i - lo] = new int[]{i, getP(i)};
        }
        quickSort(nums, 0, nums.length - 1, k);
        return nums[k - 1][0];
    }

    private void quickSort(int[][] nums, int l, int r, int k) {
        if (l >= r) {
            return;
        }
        int m = getMiddle(nums, l, r);
        if (m == k - 1) {
            return;
        } else if (m > k - 1) {
            quickSort(nums, l, m - 1, k);
        } else {
            quickSort(nums, m + 1, r, k);
        }
    }

    private int getMiddle(int[][] nums, int l, int r) {
        int k = l - 1;
        for (int i = l; i < r; ++i) {
            if ((nums[i][1] != nums[r][1] ? nums[i][1] - nums[r][1] : nums[i][0] - nums[r][0]) < 0) {
                swap(nums, ++k, i);
            }
        }
        swap(nums, ++k, r);
        return k;
    }

    private void swap(int[][] nums, int a, int b) {
        int[] temp = nums[a];
        nums[a] = nums[b];
        nums[b] = temp;
    }

    private int getP(int x) {
        int c = 0;
        while (x != 1) {
            if ((x & 1) == 1) {
                x += (x << 1) + 1;
            } else {
                x >>= 1;
            }
            ++c;
        }
        return c;
    }
}
