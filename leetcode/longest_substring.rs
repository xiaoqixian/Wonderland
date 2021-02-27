/**********************************************
  > File Name		: longest_substring.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 27 Feb 2021 03:07:49 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/*
 * Leetcode 395: find the longest substring, and every character exists in the substring has to
 * repeat at least k times.
 *
 * In Rust, string processing is always a tricky problem.
 * We can first count the number of times all characters appear in the string.
 * Then we just need to find a substring with all characters repeat more than k times.
 */

use std::collections::HashMap;

struct Solution {}

use std::cmp;

impl Solution {
    pub fn longest_substring(s: String, k: i32) -> i32 {
        let mut res = 0;
        let len = s.len();
        let chars: Vec<char> = s.chars().collect();
        for t in 1..27 {
            let mut l: usize = 0;
            let mut r: usize = 0;
            let mut count: Vec<i32> = vec![0; 26];
            let mut tot = 0;
            let mut less = 0;
            while r < len {
                count[(chars[r] as u32 - 'a' as u32) as usize] += 1;
                if count[(chars[r] as u32 - 'a' as u32) as usize] == 1 {
                    tot += 1;
                    less += 1;
                }
                if count[(chars[r] as u32 - 'a' as u32) as usize] == k {
                    less -= 1;
                }
                while tot > t {
                    count[(chars[l] as u32 - 'a' as u32) as usize] -= 1;
                    if count[(chars[l] as u32 - 'a' as u32) as usize] == k - 1 {
                        less += 1;
                    }
                    if count[(chars[l] as u32 - 'a' as u32) as usize] == 0 {
                        tot -= 1;
                        less -= 1;
                    }
                    l += 1;
                }
                if less == 0 {
                    res = cmp::max(res, r as i32 - l as i32 + 1);
                }
                r += 1;
            }
        }
        res
    }
}


fn main() {
    Solution::longest_substring(String::from("aaaccsdsd"), 2);
}
