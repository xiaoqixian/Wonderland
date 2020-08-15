/**********************************************
  > File Name		: canThreePartsEqualSum.java
  > Author			: lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 16 Aug 2020 12:08:02 AM CST
 **********************************************/

/*
  Leetcode 1013.将数组分成和相等的三个部分
  
  基本思想：先求出总和，如果可以被3整除，则继续。
  从左到右遍历数组，如果左边子数组之和等于总和的1/3，则得到i，同样可以得到j

  其实leetcode的时间占用实属玄学，同样的代码运行两次击败比例差好多
 */

class Solution {
    public boolean canThreePartsEqualSum(int[] A) {
        int sum = 0;
        for (int i : A) {
            sum += i;
        }
        if (sum % 3 != 0) {
            return false;
        }
        int aThird = sum / 3, tmp = 0, count = 0;
        //System.out.println("A third: " + aThird);
        for (int j = 0; j < A.length; j++) {
            tmp += A[j];
            //System.out.println("tmp: " + tmp);
            if (tmp == aThird) {
                tmp = 0;
                count++;
            }
            if (count == 2) {
                if (j == A.length - 1) {
                    count--;
                }
                break;
            }
        }
        if (count == 2) {
            return true;
        }
        return false;
    }
}
