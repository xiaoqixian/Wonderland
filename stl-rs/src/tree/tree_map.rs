/**********************************************
  > File Name		: TreeMap.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 15 Feb 2022 09:55:35 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::ptr::NonNull;

/**
 * Red Black Tree Features:
 *  1. Every node is either black or red
 *  2. The root node must be black
 *  3. Every empty leaf node must be black
 *  4. If a node is black, its children nodes must be black
 *  5. Any path from a node to one of its any children node 
 *     must contain a same number of black nodes. This makes
 *     sure the tree is always balanced.
 */
#[derive(Debug, Clone, Copy)]
enum Color {
    Black,
    Red
}

struct TreeNode<K, V> where K: Ord + Eq {
    color: Color,
    k: K,
    v: V,
    left: Option<NonNull<Self>>,
    right: Option<NonNull<Self>>,
}
