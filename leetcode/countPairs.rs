/**********************************************
  > File Name		: countPairs.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu 17 Feb 2022 11:45:37 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/


// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
  pub val: i32,
  pub left: Option<Rc<RefCell<TreeNode>>>,
  pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
  #[inline]
  pub fn new(val: i32) -> Self {
    TreeNode {
      val,
      left: None,
      right: None
    }
  }
}

use std::rc::Rc;
use std::cell::RefCell;
type Node = Rc<RefCell<TreeNode>>;

impl Solution {
    pub fn count_pairs(root: Option<Node>, d: i32) -> i32 {
        let mut res: usize = 0;
        Self::dfs(root, d as usize, &mut res);
        res as i32
    }

    fn dfs(r: Option<Node>, distance: usize, res: &mut usize) -> Vec<usize> {
        if r.is_none() {return Vec::new();}

        let root = r.unwrap();
        if root.borrow().left.is_none() && root.borrow().right.is_none() {
            return vec![0];
        }

        let mut ret = Vec::<usize>::new();
        let mut left = Self::dfs(root.borrow().left.clone(), distance, res);
        for l in left.iter_mut() {
            *l += 1;
            if *l <= distance {
                ret.push(*l);
            }
        }

        let mut right = Self::dfs(root.borrow().right.clone(), distance, res);
        for r in right.iter_mut() {
            *r += 1;
            if *r <= distance {
                ret.push(*r);
            }
        }

        for l in left.iter() {
            for r in right.iter() {
                if l + r <= distance {*res += 1;}
            }
        }

        ret
    }
}
