/**********************************************
 *> File Name		: regionBySlashes.java
 *> Author			: lunar
 *> Email			: lunar_ubuntu@qq.com
 *> Created Time	: Sat 01 Aug 2020 11:12:21 AM CST
 **********************************************/

/*
 Leetcode 959.由斜杠划分区域

 既然这题分在了幷查集里面，自然要用幷查集的思想去做。

 将正方形看做一个图，不断往里面加入边，如果新加边的两个端点可以通往一个根节点，就代表形成了一个环，就代表
 形成了一个新的区域。
 */

/*
 之前一直想着要用两个坐标表示一个节点。看了别人的答案后想起来完全可以把二维数组铺开成一个一维数组
 这样就比较好解决了。不然原先要用三维数组才能表示。
 */
class Solution {
    public int regionsBySlashes(String[] grid) {
        int[] nums = new int[(grid.length+1) * (grid.length+1)+1];
        //为了避免还要进行一次初始化，当数组值为0时表示没有父节点。
        //这样就不能表示索引为0的节点，所以数组要多出来一个数。
        //这样索引为0的数就变成了索引为1的数
        //进行数组的初始化，将正方形的边初始化为根节点都是左上角的节点
        int offset;
        for (int i = 0; i <= grid.length; i++) {
            offset = i * grid.length;
            if (i == 0 || i == grid.length) {
                for (int j = 0; j <= grid.length; j++) {
                    nums[offset + j + 1] = 1;
                }
            } else {
                nums[offset + 1] = 1;
                nums[offset + grid.length + 1] = 1;
            }
        }
        int left, right, res = 1; //即使没有线，也是一个区域
        for (int i = 0; i < grid.length; i++) {
            String s = grid[i];
            for (int j = 0; j < s.length(); j++) {
                char c = s.charAt(j);
                if (c == ' ') {
                    continue;
                }
                else if (c == '/') {
                    left = i*grid.length + j + 2;
                    right = (i+1)*grid.length + j + 1;
                    if (isRing(left, right, nums)) {
                        res++;
                    }
                }
                else {
                    left = i*grid.length + j + 1;
                    right = (i+1)*grid.length + j + 2;
                    if (isRing(left, right, nums)) {
                        res++;
                    }
                }
            }
        }
        return res;
    }

    public boolean isRing(int left, int right, int[] nums) {
        //如果两个点都没有父节点，则令右节点的父节点是左节点，左节点的父节点是自己
        //如果是一个节点有父节点，则令无父节点的节点的父节点为有父节点的节点的父节点
        //如果两个都有父节点，则判断父节点是否相同，相同则判断有环，返回true。
        //没有则需要合并两个集合，返回false
        if (nums[left] == 0 && nums[right] == 0) {
            nums[left] = left;
            nums[right] = left;
            return false;
        }
        else if (nums[left] == 0) {
            nums[left] = right;
            return false;
        }
        else if (nums[right] == 0) {
            nums[right] = left;
            return false;
        }
        else {
            //找到两个根节点
            int leftRoot = left, rightRoot = right;
            while (nums[leftRoot] != leftRoot) {
                //懒得做路径压缩了
                leftRoot = nums[leftRoot];
            }
            while (nums[rightRoot] != rightRoot) {
                rightRoot = nums[rightRoot];
            }
            if (rightRoot == leftRoot) {
                nums[left] = leftRoot;
                nums[right] = rightRoot;
                return true;
            }
            else {
                nums[leftRoot] = rightRoot;
                nums[left] = rightRoot;
                nums[right] = rightRoot;
                return false;
            }
        }
    }
}
