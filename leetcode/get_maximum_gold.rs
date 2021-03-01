/**********************************************
  > File Name		: get_maximum_gold.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 28 Feb 2021 08:34:43 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/*
 * Leetcode 1219: Gold Miner.
 * Using backtracking algorithm.
 * We let the miner always goes toward the right bottom corner.
 */

struct Solution {}

impl Solution {
    pub fn get_maximum_gold(grid: Vec<Vec<i32>>) -> i32 {
        let height = grid.len();
        let width = grid[0].len();
        let mut been: Vec<Vec<bool>> = vec![vec![false; width]; height];
        let mut res = 0;
        for i in 0..height {
            for k in 0..width {
                let track_max = Self::track(&grid, &mut been, i, k);
                if track_max > res {
                    res = track_max;
                }
            }
        }
        res
    }

    fn track(grid: &Vec<Vec<i32>>, been: &mut Vec<Vec<bool>>, height: usize, width: usize) -> i32 {
        if grid[height][width] == 0 || been[height][width] {
            return 0;
        }
        been[height][width] = true;
        let mut max = 0;
        if height > 0 {
            let up = Self::track(grid, been, height-1, width);
            if up > max {
                max = up;
            }
        }
        if height + 1 < grid.len() {
            let down = Self::track(grid, been, height+1, width);
            if down > max {
                max = down;
            }
        }
        if width > 0 {
            let left = Self::track(grid, been, height, width-1);
            if left > max {
                max = left;
            }
        }
        if width + 1 < grid[0].len() {
            let right = Self::track(grid, been, height, width+1);
            if right > max {
                max = right;
            }
        }
        been[height][width] = false;//the essential of the backtracking algorithm.
        grid[height][width] + max
    }
}

fn main() {

}
