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

    #[inline]
    fn next(&self, layer: usize) -> Option<Rc<Self>> {
        self.layers.borrow().get(layer).unwrap().clone()
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

impl<T> SkipList<T> where T: std::fmt::Display {
    fn random_level() -> usize {
        let mut res: usize = 1;
        let mut deno: u32 = 2;
        let mut rng = rand::thread_rng();
        
        while res < MAX_LEVEL && rng.gen_ratio(1, deno) {
            res += 1;
            deno <<= 1;
        }
        res
    }

    fn find_at_layer(&self, mut cursor: Rc<SkipListNode<T>>, layer: usize, target: &T) 
        -> Rc<SkipListNode<T>> where T: Ord {

        if layer >= self.level {return cursor;}

        loop {
            cursor = match cursor.next(layer) {
                Some(next_node) if &next_node.val < target => next_node.clone(),
                _ => break
            };
        }
        cursor
    }

    pub fn add(&mut self, val: T) where T: Ord {
        let mut update: Vec::<Option<Rc<SkipListNode<T>>>> = vec![None; MAX_LEVEL];
        let mut cursor = self.head.clone();

        let mut index = self.level;
        while index > 0 {
            index -= 1;
            cursor = self.find_at_layer(cursor, index, &val);
            update[index] = Some(cursor.clone());
        }

        let lv = {
            let mut lv = Self::random_level();
            if lv > self.level {
                self.level += 1;
                lv = self.level;
                update[lv - 1] = Some(self.head.clone());
            }
            lv
        };

        let new_node = Rc::new(SkipListNode::<T>::new(val, lv));
        let mut new_node_layers = new_node.layers.borrow_mut();
        index = lv;

        while index > 0 {
            index -= 1;
            let p = update.get(index).unwrap().as_ref().unwrap().clone();
            (*new_node_layers)[index] = match p.layers.borrow().get(index).unwrap() {
                None => None,
                Some(v) => Some(v.clone())
            };
            (*p.layers.borrow_mut())[index] = Some(new_node.clone());
        }
    }

    pub fn erase(&mut self, target: T) -> bool where T: Ord {
        let mut update: Vec<Option<Rc<SkipListNode<T>>>> = vec![None; MAX_LEVEL + 1];
        let mut cursor = self.head.clone();
        let mut i = self.level;

        while i > 0 {
            i -= 1;
            cursor = self.find_at_layer(cursor, i, &target);
            update[i] = Some(cursor.clone());
        }

        //cursor = cursor.clone().layers.borrow().get(0).unwrap().as_ref().unwrap().clone();
        cursor = cursor.next(0).unwrap();
        if cursor.val != target {
            return false;
        }

        i = 0;
        while i < self.level {
            match update.get(i).unwrap().as_ref().unwrap().layers.borrow().get(i).unwrap() {
                Some(skiplist_node) if skiplist_node == &cursor => {},
                _ => break
            }
            println!("layers length = {}", cursor.layers.borrow().len());
            (*update[i].as_ref().unwrap().layers.borrow_mut())[i] = match cursor.layers.borrow().get(i) {
                Some(node) if node.is_some() => node.clone(),
                _ => None
            };
            i += 1;
        }

        while self.level > 0 && match self.head.layers.borrow().get(self.level-1) {
            Some(node) if node.is_some() => node.as_ref().unwrap() == &self.tail,
            _ => false
        } { //head layers are always be Some.
            self.level -= 1;
        }
        true
    }

    pub fn query(&self, target: T) -> bool where T: Ord {
        let mut height = self.level;
        let mut cursor = self.head.clone();
        
        while height > 0 {
            height -= 1;
            cursor = self.find_at_layer(cursor, height, &target);
        }
        //cursor = cursor.clone().layers.borrow().get(0).unwrap().as_ref().unwrap().clone();
        cursor = cursor.next(0).unwrap();
        cursor.val == target
    }
}

fn main() {
    for i in 0..6 {
        println!("{}", i);
    }
}

