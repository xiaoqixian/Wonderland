/**********************************************
  > File Name		: TreeMap.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 15 Feb 2022 09:55:35 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::cmp::{Ord, Eq, PartialEq, PartialOrd, Ordering};

struct TreeNode<K, V> where K: Ord + Eq {
    k: K,
    v: V,
    left: Option<Box<Self>>,
    right: Option<Box<Self>>
}

impl<K, V> TreeNode<K, V> where K: Ord + Eq {
    fn new(k: K, v: V) -> Box<Self> {
        Box::new(Self {
            k,
            v,
            left: None,
            right: None
        })
    }

    fn cmp_key(&self, k: &K) -> Ordering {
        self.k.cmp(k)
    }

    fn get_v<'a>(&'a self) -> &'a V {
        &self.v
    }

    fn get_mut_v<'a>(&'a mut self) -> &'a mut V {
        &mut self.v
    }
}

impl<K, V> PartialEq for TreeNode<K, V> where K: Ord + Eq {
    fn eq(&self, other: &Self) -> bool {
        self.k.eq(&other.k)
    }
}

impl<K, V> Eq for TreeNode<K, V> where K: Ord + Eq {}

impl<K, V> PartialOrd for TreeNode<K, V> where K: Ord + Eq {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(Ord::cmp(self, other))
    }
}

impl<K, V> Ord for TreeNode<K, V> where K: Ord + Eq {
    fn cmp(&self, other: &Self) -> Ordering {
        self.k.cmp(&other.k)
    }
}


struct TreeMap<K, V> where K: Ord + Eq {
    root: Option<Box<TreeNode<K, V>>>
}

impl<K, V> super::Map<K, V> for TreeMap<K, V> 
where K: Ord + Eq {
    fn insert(&mut self, k: K, v: V) -> Option<V> {
        if self.root.is_none() {
            self.root = Some(TreeNode::new(k, v));
            return None;
        }
        None
    }

    fn get<'a>(&'a self, k: &K) -> Option<&'a V> {
        match self.root {
            None => None,
            Some(ref root) => {
                let mut cursor = root;
                loop {
                    match cursor.cmp_key(k) {
                        Ordering::Equal => return Some(cursor.get_v()),
                        Ordering::Less => match cursor.left.as_ref() {
                            None => return None,
                            Some(v) => cursor = v
                        },
                        Ordering::Greater => match cursor.right.as_ref() {
                            None => return None,
                            Some(v) => cursor = v
                        }
                    }
                }
            }
        }
    }

    fn get_mut<'a>(&'a mut self, k: &K) -> Option<&'a mut V> {
        match self.root {
            None => None,
            Some(ref mut root) => {
                let mut cursor = root;
                loop {
                    match cursor.cmp_key(k) {
                        Ordering::Equal => return Some(cursor.get_mut_v()),
                        Ordering::Less => match cursor.left.as_mut() {
                            None => return None,
                            Some(v) => cursor = v
                        },
                        Ordering::Greater => match cursor.right.as_mut() {
                            None => return None,
                            Some(v) => cursor = v
                        }
                    }
                }
            }
        }
    }

    fn remove(&mut self, k: &K) -> Option<V> {
        None
    }
}
    
