// Date: Sun Oct 01 22:16:08 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

struct Solution;

impl Solution {
    fn maximum_triplet_value(nums: Vec<i32>) -> i64 {
        let n = nums.len();
        let prefix_max: Vec<i32> = 
            nums.iter().scan(nums[0], |state, &x| {
                *state = std::cmp::max(*state, x);
                Some(*state)
        }).collect();
        let suffix_max: Vec<i32> = 
            nums.iter().rev().scan(nums[n-1], |state, &x| {
                *state = std::cmp::max(*state, x);
                Some(*state)
            }).collect();

        (1..n-1).fold(0, |res: i64, j: usize| {
            std::cmp::max(res, 
                (prefix_max[j-1] as i64 - nums[j] as i64) * (suffix_max[n-j-2] as i64)
            )
        })
    }
}

fn main() {
    let res = Solution::maximum_triplet_value(vec![12,6,1,2,7]);
    println!("{}", res);
}
