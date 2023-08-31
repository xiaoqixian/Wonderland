// Date: Wed Aug 30 22:33:56 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

use std::cell::RefCell;

struct Solution();

impl Solution {
    pub fn get_max_function_value(_receiver: Vec<i32>, k: i64) -> i64 {
        let receiver: Vec<usize> = _receiver.iter().map(|e| *e as usize).collect();
        let n = receiver.len();
        let mut ring_info: Vec<Option<(usize, usize)>> = vec![None; n];
        let mut rings = Vec::<Vec<usize>>::new();
        let mut degrees = vec![0; n];
        let mut visited: Vec<RefCell<bool>> = vec![RefCell::new(false); n];
        let mut res: i64 = 0;

        receiver.iter().enumerate().for_each(|(pos, e)| {
            degrees[pos] -= 1;
            degrees[*e] += 1;
        });

        let mut dfs = |start_id: usize| {
            let mut st = vec![start_id];
            while !st.is_empty() {
                let id = *st.last().unwrap();
                if !*visited[id].borrow() {
                    st.push(receiver[id]);
                    visited[id].replace(true);
                    continue;
                }

                st.pop();
                if let Some(_) = ring_info[id] {
                    continue;
                }

                match ring_info[receiver[id]] {
                    Some(next) => {
                        ring_info[id] = Some((next.0+1, next.1));
                    },
                    None => {
                        let ring_index = rings.len();
                        let mut ring = vec![id];
                        ring_info[id] = Some((0, ring_index));
                        let mut rid = receiver[id];
                        
                        while rid != id {
                            ring.push(rid);
                            ring_info[rid] = Some((0, ring_index));
                            rid = receiver[rid];
                            st.pop();
                        }

                        rings.push(ring);
                    }
                }
            }
        };

        (0..n)
            .filter(|id| degrees[*id] < 0)
            .for_each(&mut dfs);
        (0..n)
            .filter(|id| !*visited[*id].borrow() && degrees[*id] == 0)
            .for_each(&mut dfs);

        visited = vec![RefCell::new(false); n];
        let ring_sum: Vec<usize> = rings.iter()
            .map(|ring| ring.iter().sum())
            .collect();

        let mut start_from = |start_id: usize| {
            let mut sum: i64 = 0;
            let mut step: i64 = k;
            let (dist, ring_index) = ring_info[start_id].unwrap();

            let limit = std::cmp::min(dist as i64, step);
            step -= limit as i64;
            let mut rid = start_id;

            for _ in 0..limit as usize {
                sum += rid as i64;
                rid = receiver[rid];
            }

            if step > 0 {
                sum += (step / rings[ring_index].len() as i64) * ring_sum[ring_index] as i64;
                for _ in 0..(step % rings[ring_index].len() as i64) {
                    sum += rid as i64;
                    rid = receiver[rid];
                }
            }

            sum += rid as i64;

            res = std::cmp::max(res, sum);
            visited[start_id].replace(true);
            let mut sid = start_id;

            while !*visited[receiver[sid]].borrow() {
                sum -= sid as i64;
                sid = receiver[sid];
                rid = receiver[rid];
                sum += rid as i64;
                res = std::cmp::max(res, sum);
                visited[sid].replace(true);
            }
        };

        (0..n).filter(|id| degrees[*id] < 0)
            .for_each(&mut start_from);
        (0..n).filter(|id| !*visited[*id].borrow() && degrees[*id] == 0)
            .for_each(&mut start_from);

        res
    }
}

fn main() {
    let receiver = vec![1,1,1,2,3];
    Solution::get_max_function_value(receiver, 3);
}
