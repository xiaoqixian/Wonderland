/**********************************************
  > File Name		: build_tree.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 15 Apr 2022 02:02:52 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::rc::Rc;
use std::cell::RefCell;
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

struct Solution;

/*
 * preorder: [root, [left child tree], [right child tree]]
 * inorder:  [[left child tree], root, [right child tree]] 
 */
impl Solution {
    pub fn build_tree(preorder: Vec<i32>, inorder: Vec<i32>) -> Option<Rc<RefCell<TreeNode>>> {
        if preorder.is_empty() {return None;}

        Self::_build_tree(&preorder, &inorder, (0, preorder.len()-1), (0, inorder.len()-1))
    }

    fn _build_tree(preorder: &Vec<i32>, inorder: &Vec<i32>, pre_bound: (usize, usize), 
        in_bound: (usize, usize)) -> Option<Rc<RefCell<TreeNode>>> {
        
        let root = Rc::new(RefCell::new(TreeNode::new(preorder[pre_bound.0])));

        if pre_bound.0 == pre_bound.1 {return Some(root);}

        let in_root_index = {
            let mut i = in_bound.0;
            let root_val = preorder[pre_bound.0];
            while inorder[i] != root_val {i += 1;}
            i
        };

        let mut left_tree_len: usize = 0;
        if in_root_index > in_bound.0 {
            left_tree_len = in_root_index - in_bound.0;
            (*root.borrow_mut()).left = Self::_build_tree(preorder, inorder, 
                (pre_bound.0 + 1, pre_bound.0 + left_tree_len),
                (in_bound.0, in_root_index - 1));
        }

        if in_root_index < in_bound.1 {
            let right_tree_len = in_bound.1 - in_root_index;
            (*root.borrow_mut()).right = Self::_build_tree(preorder, inorder, 
                (pre_bound.0 + left_tree_len + 1, pre_bound.1),
                (in_root_index + 1, in_bound.1));
        }

        Some(root)
    }
}
