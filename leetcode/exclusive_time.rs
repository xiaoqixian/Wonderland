/**********************************************
  > File Name		: exclusive_time.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Aug  7 23:50:52 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

struct Solution;

impl Solution {
    pub fn exclusive_time(n: i32, logs: Vec<String>) -> Vec<i32> {
        let mut clock = 0;
        let mut res = vec![0; n as usize];
        let mut stack = Vec::<usize>::new();
        let mut last_end = false;

        for log in logs {
            let mut log_split = log.split(":");
            let id = log_split.next().unwrap().parse::<usize>().unwrap();
            let se = log_split.next().unwrap();
            let time = log_split.next().unwrap().parse::<i32>().unwrap();

            match se {
                "start" => {
                    if let Some(last) = stack.last() {
                        res[*last] += time - clock;
                        if last_end {res[*last] -= 1;}
                    }
                    stack.push(id);
                    last_end = false;
                },
                "end" => {
                    let last = stack.pop().unwrap();
                    *res.get_mut(last).unwrap() += time - clock;
                    if !last_end {res[last] += 1;}
                    last_end = true;
                },
                _ => panic!("unexpected se {}", se)
            }

            clock = time;
        }
        res
    }
}

fn main() {}
