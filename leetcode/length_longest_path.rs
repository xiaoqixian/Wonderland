/**********************************************
  > File Name		: length_longest_path.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 20 Apr 2022 11:06:50 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

struct Solution;

impl Solution {
    pub fn length_longest_path(input: String) -> i32 {
        let mut levels = Vec::<usize>::new();
        let mut res: usize = 0;
        let mut level_index: usize = 0;
        let mut curr_path_len: usize = 0;
        let mut first_letter: bool = true;
        let mut is_file: bool = false;
        
        for c in input.chars() {
            print!("char: ");
            match c {
                '\n' => println!("\\n"),
                '\t' => println!("\\t"),
                c => println!("{}", c)
            }
            match c {
                '\n' => {
                    level_index = 0;

                    if is_file && curr_path_len + levels.len() - 1 > res {
                        res = curr_path_len + levels.len() - 1;
                        is_file = false;
                        println!("res = {}", res);
                    }
                    first_letter = true;
                },
                '\t' => {
                    level_index += 1;
                },
                _ if first_letter => {
                    while level_index < levels.len() {
                        curr_path_len -= match levels.pop() {
                            None => break,
                            Some(v) => v
                        };
                    }
                    levels.push(1);
                    curr_path_len += 1;
                    first_letter = false;
                },
                c => {
                    levels[level_index] += 1;
                    curr_path_len += 1;
                    if c == '.' {
                        is_file = true;
                    }
                }
            }
        }

        if is_file && curr_path_len + levels.len() - 1 > res {
            res = curr_path_len + levels.len() - 1;
        }

        res as i32
    }
}

#[derive(Debug)]
struct A {
    i: i32
}

impl std::ops::Add for &A {
    type Output = A;
    fn add(self, rhs: Self) -> Self::Output {
        A {
            i: self.i + rhs.i
        }
    }
}

fn main() {
    println!("{}", Solution::length_longest_path(String::from("a")));
    //println!("{}", Solution::length_longest_path(String::from("dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext")));
}
