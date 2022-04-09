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

use rand::prelude::*;

struct Node<T> where T: Ord + Eq {
    val: T,
    next: RefCell<Option<Rc<Self>>>,
    next_level_node: RefCell<Option<Rc<Self>>>
}

trait LinkedListNode {
    type Output;
    fn next(&self) -> Self::Output;

    fn set_next(&self, next: Self::Output);
}

struct LinkedList<T> where T: LinkedListNode + Clone {
    head: Option<T>,
    tail: Option<T>,
    size: usize
}

impl<T> LinkedListNode for Node<T> where T: Ord + Eq {
    type Output = Option<Rc<Self>>;
    fn next(&self) -> Self::Output {
        self.next.borrow().clone()
    }

    fn set_next(&self, next: Self::Output) {
        assert!(next.is_some());
        let old_next = self.next.replace(next.clone());
        *next.as_ref().unwrap().next.borrow_mut() = old_next;
    }
}

impl<T> PartialEq for Node<T> where T: Ord + Eq {
    fn eq(&self, other: &Self) -> bool {
        self.val == other.val
    }
}

impl<T> Eq for Node<T> where T: Ord + Eq {}

impl<T> Ord for Node<T> where T: Ord + Eq {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.val.cmp(&other.val)
    }
}

impl<T> PartialOrd for Node<T> where T: Ord + Eq {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl<T> Node<T> where T: Ord + Eq {
    fn new(val: T) -> Self {
        Self {
            val,
            next: RefCell::new(None),
            next_level_node: RefCell::new(None)
        }
    }
}

impl<T> LinkedList<T> where T: LinkedListNode + Clone + Ord + Eq {
    fn new() -> Self {
        Self {
            head: None,
            tail: None,
            size: 0
        }
    }

    //append a new node after node.
    fn append_after(&mut self, node: T, new_node: T) {
        if self.tail.is_some() && self.tail.as_ref().unwrap() == &node {
            self.tail = Some(new_node.clone());
        }
        node.set_next(new_node);
        self.size += 1;
    }
}

struct SkipList<T> where T: Ord + Eq {
    list: Vec<LinkedList<Node<T>>>,
    rng: ThreadRng
}



fn main() {
    
}
