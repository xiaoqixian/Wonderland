// Date:   Sun Mar 31 19:36:55 2024
// Mail:   lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

package main

func countAlternatingSubarrays(nums []int) int64 {
    var sub_len []int;
    n := len(nums)
    for start, end := 0, 1; start < n; {
        end = start + 1;
        for end < n && nums[end] == nums[end-1] {
            end++;
        }

        sub_len = append(sub_len, end - start)
        start = end
    }

    var res int64 = 0;
    for _, l := range sub_len {
        res += int64(l+1) * int64(l) / 2
    }
    return res
}

func main() {
    _ = countAlternatingSubarrays([]int{ 1,2,3 })
}
