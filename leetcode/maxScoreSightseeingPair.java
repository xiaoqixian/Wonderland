/**********************************************
  > File Name		: maxScoreSightseeingPair.java
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 20 Aug 2020 12:20:36 AM CST
 **********************************************/

/*
 Leetcode 1014.最佳观光组合

 看起来像是动态规划问题
 目标是保证只有O(n)的复杂度

 准备两个指针i和j，在i=0时，找到最优解j。总是记最优解的i为start，j为end
 然后对于i逐渐遍历
 当i < end时，如果A[i] + i > A[start] + start。则令start = i。更新结果

 当i > end时，则前面的最大值作为一个阶段的最大值保存起来。然后重新确定一个start和end。直到i = A.length - 1
 */

class Solution {
    public int maxScoreSightseeingPair(int[] a) {
        int start = 0, end = 0, max = 0, res = 0;
        //找到初次的最优解
        for (int i = 1; i < a.length; i++) {
            if (max < a[i] - i) {
                max = a[i] - i;
                end = i;
            }
        }
        max += a[start];
        res = max;
        //System.out.println("初始end: " + end + ", max: " + max);
        for (int i = 1; i < a.length-1; i++) {
            int diff = a[i] + i - a[start] - start;
            if (i < end) {
                if (diff > 0) {
                    start = i;
                    max = a[i] + a[end] + i - end;
                }
            } else if (i == end){
                if (res < max) {
                    res = max;
                }
                max = 0;
                //找到新的end
                start = end;
                for (int j = i+1; j < a.length; j++) {
                    if (max < a[j] + a[i] + i - j) {
                        max = a[j] + a[i] + i - j;
                        end = j;
                    }
                }
                //System.out.println("新的一段: [" + start + ", " + end + "]");
            }
        }
        if (res < max) {
            res = max;
        }
        return res;
    }
}

/*
 * 实际存在一种更简单的解法
 * 由于结果res = A[i] + A[j] - j + i为A[i] + i和A[j] - j两部分组成
 * 所以只要保证这两部分最大就好了。
 * A[i] + i总是为当前区间上的最大值。
 */

class Solution {
    public int maxScoreSightseeingPair(int[] A) {
        int ans = 0, mx = A[0] + 0;
        for (int j = 1; j < A.length; ++j) {
            ans = Math.max(ans, mx + A[j] - j);
            // 边遍历边维护
            mx = Math.max(mx, A[j] + j);
        }
        return ans;
    }
}

/*
作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/best-sightseeing-pair/solution/zui-jia-guan-guang-zu-he-by-leetcode-solution/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
