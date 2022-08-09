/**********************************************
  > File Name		: min_path_cost.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue Aug  9 20:58:43 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

struct Solution;

impl Solution {
    pub fn min_path_cost(mut grid: Vec<Vec<i32>>, _move_cost: Vec<Vec<i32>>) -> i32 {
        let (m, n) = (grid.len(), grid[0].len());
        let mut move_cost: Vec<Vec<i32>> = Vec::with_capacity(m*n);

        for _ in 0..m*n {
            move_cost.push(vec![0; n]);
        }

        for i in 0..(m-1) {
            let (row, next_row) = (&grid[i], &grid[i+1]);
            for k in 0..n {
                for j in 0..n {
                    move_cost[next_row[k] as usize][j] = _move_cost[row[j] as usize][k];
                }
            }
        }

        for i in 1..m {
            for k in 0..n {
                let number = grid[i][k] as usize;
                let min_cost = move_cost.get(number).unwrap().iter().zip(grid.get(i-1).unwrap().iter()).map(|(&b, &v)| b + v).reduce(|accum, item| if accum < item {accum} else {item}).unwrap();
                grid[i][k] += min_cost;
            }
        }

        *grid.get(m-1).unwrap().into_iter().reduce(|accum, item| if accum < item {accum} else {item}).unwrap()
    }
}

fn main() {
    let grid = vec![vec![5,3],vec![4,0],vec![2,1]];
    let mc = vec![vec![9,8],vec![1,5],vec![10,12],vec![18,6],vec![2,4],vec![14,3]];

    println!("{}", Solution::min_path_cost(grid, mc));
}
