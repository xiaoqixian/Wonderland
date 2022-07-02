/**********************************************
  > File Name		: is_monotonic.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 28 Feb 2021 07:43:57 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/*
 * Leetcode 896: decides if an array is monotonic
 */

impl Solution {
    pub fn is_monotonic(a: Vec<i32>) -> bool {
        if a.len() == 1 {
            return true;
        }
        let mut initialed = false;
        let mut inc = false;
        let mut index = 0;
        while index < a.len() - 1 && a[index] == a[index+1] {
            index += 1;
        }
        if index == a.len() - 1 {
            return true;//all elements are the same.
        }
        if a[index] < a[index+1] {
            inc = true;
        }
        while index < a.len() - 1 {
            if inc && a[index] > a[index+1] {
                return false;
            } else if !inc && a[index] < a[index+1] {
                return false;
            }
            index += 1;
        }
        true
    }
 }
