/**********************************************
  > File Name		: SkipList.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 04 Apr 2022 06:54:51 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::rc::Rc;
use std::cell::RefCell;

const MAX_LEVEL: usize = 32;

struct SkipListNode<T> {
    val: T,
    layers: RefCell<Vec<Option<Rc<Self>>>>
}

impl<T> PartialEq for SkipListNode<T>
where T: Eq {
    fn eq(&self, other: &Self) -> bool {
        self.val == other.val
    }
}

impl<T> Eq for SkipListNode<T> where T: Ord {}

impl<T> Ord for SkipListNode<T>
where T: Ord {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.val.cmp(&other.val)
    }
}

impl<T> PartialOrd for SkipListNode<T>
where T: Ord {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl<T> SkipListNode<T> {
    fn new(val: T, size: usize) -> Self {
        Self {
            val,
            layers: RefCell::new(vec![None; size])
        }
    }
}

struct SkipList<T> {
    level: usize,
    head: Rc<SkipListNode<T>>,
    tail: Rc<SkipListNode<T>>
}

impl SkipList<i32> {
    fn new() -> Self {
        let tail = Rc::new(SkipListNode::<i32>::new(std::i32::MAX, 0));
        let head = SkipListNode::<i32>::new(std::i32::MAX, MAX_LEVEL);
        {
            let mut head_layers = head.layers.borrow_mut();

            for i in 0..MAX_LEVEL {
                (*head_layers)[i] = Some(tail.clone());
            }
        }
            
        Self {
            level: 0,
            head: Rc::new(head),
            tail
        }
    }
}

impl<T> SkipList<T> {
    fn random_level() -> usize {
        return 0;
    }

    pub fn add(&mut self, val: T) where T: Ord {
        let mut update = Vec::<Rc<SkipListNode<T>>>::with_capacity(MAX_LEVEL);
        let mut cursor = self.head.clone();

        let mut index = self.level-1;
        while index >= 0 {
            loop {
                cursor = match cursor.clone().layers.borrow().get(index) {
                    Some(skiplist_node) => {
                        match skiplist_node {
                            Some(node) if node < &cursor => node.clone(),
                            _ => break
                        }
                    },
                    None => break
                };
            }
            update[index] = cursor.clone();
            index -= 1;
        }

        let lv = {
            let mut lv = Self::random_level();
            if lv > self.level {
                self.level += 1;
                lv = self.level;
                update[lv - 1] = self.head.clone();
            }
            lv
        };

        let new_node = Rc::new(SkipListNode::<T>::new(val, lv));
        let mut new_node_layers = new_node.layers.borrow_mut();
        index = lv - 1;
        while index >= 0 {
            let p = update[index].clone();
            (*new_node_layers)[index] = match p.layers.borrow().get(index).unwrap() {
                None => None,
                Some(v) => Some(v.clone())
            };
            (*p.layers.borrow_mut())[index] = Some(new_node.clone());
        }
    }

    pub fn erase(target: T) where T: Ord -> bool {
        let mut update = Vec::<Rc<SkipListNode<T>>>::with_capacity(MAX_LEVEL + 1);
        let mut head = self.head.clone();
        let mut head = self.head.clone();
    }
}

fn main() {
    for i in 0..6 {
        println!("{}", i);
    }
}

