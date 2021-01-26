/**********************************************
  > File Name		: buddy_strings.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 26 Jan 2021 11:24:08 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/*
 * Solution:
 * 1. Compart two strings, if there are more than two different letters or only one different
 *    letters, then returns false.
 * 2. After two letters changed, if two strings are the same, returns true.
 */

struct Solution {

}

impl Solution {
    pub fn buddy_strings(a: String, b: String) -> bool {
        if a.len() != b.len() {
            return false;
        }
        let mut a_chars = a.chars();
        let mut b_chars = b.chars();
        let mut differences = Vec::new();
        let mut count = 0;
        loop {
            let a_char = a_chars.next();
            let b_char = b_chars.next();
            if a_char == None {
                break;
            }
            if a_char != b_char {
                differences.push(count);
            }
            count += 1;
        }
        if differences.len() == 0 {
            use std::collections::HashMap;
            let mut map: HashMap<char, i32> = HashMap::new();
            for c in a.chars() {
                if map.get(&c) != None {
                    return true;
                }
                map.insert(c, 1);
            }
            return false;
        }
        if differences.len() == 1 || differences.len() > 2 {
            return false;
        }
        if a[differences[0]..(differences[0]+1)] == b[differences[1]..(differences[1]+1)] && a[differences[1]..(differences[1]+1)] == b[differences[0]..(differences[0]+1)] {
            return true;
        }
        for i in differences {
            println!("{}", i);
        }
        false
    }
}

fn main() {
    if Solution::buddy_strings(String::from("ab"), String::from("ab")) {
        println!("true");
    } else {
        println!("false");
    }
}
