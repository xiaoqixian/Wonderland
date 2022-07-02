/**********************************************
  > File Name		: LFUCache.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 25 Mar 2022 02:42:14 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::{HashMap, BTreeSet};
use std::ptr::NonNull;
use std::rc::Rc;
use std::cell::RefCell;

#[derive(Debug, Clone, Copy)]
struct Entry {
    key: i32,
    value: i32,
    get_times: usize,
    latest_time: u32
}

impl Entry {
    fn new(key: i32, value: i32, latest_time: u32) -> Self {
        Self {
            key,
            value,
            get_times: 1,
            latest_time
        }
    }
}

//impl std::borrow::Borrow<Entry> for Entry {
    //fn borrow(&self) -> &Entry {
        //self.as_ref()
    //}
//}

impl std::cmp::PartialEq for Entry {
    fn eq(&self, other: &Self) -> bool {
        if self.get_times == other.get_times {
            self.latest_time == other.latest_time
        } else {
            self.get_times == other.get_times
        }
    }
}

impl std::cmp::Eq for Entry {}

impl std::cmp::PartialOrd for Entry {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        if self.get_times == other.get_times {
            Some(self.latest_time.cmp(&other.latest_time))
        } else {
            Some(self.get_times.cmp(&other.get_times))
        }
    }
}

impl Ord for Entry {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.partial_cmp(other).unwrap()
    }
}

#[derive(Debug)]
struct LinkedListNode<T> where T: std::fmt::Debug + Clone {
    element: T,
    prev: RefCell<Option<Rc<Self>>>,
    next: RefCell<Option<Rc<Self>>>
}

impl<T> LinkedListNode<T> where T: std::fmt::Debug + Clone {
    fn new(element: T) -> Self {
        Self {
            element,
            prev: RefCell::new(None),
            next: RefCell::new(None)
        }
    }
}

struct LinkedList<T> where T: Eq + std::fmt::Debug + Clone {
    head: Option<Rc<LinkedListNode<T>>>,
    tail: Option<Rc<LinkedListNode<T>>>,
    size: usize
}

impl<T> LinkedList<T> where T: Eq + std::fmt::Debug + Clone {
    fn new() -> Self {
        Self {
            head: None,
            tail: None,
            size: 0
        }
    }

    fn size(&self) -> usize {
        self.size
    }

    fn push_back(&mut self, item: T) {
        let rc_node = Rc::new({
            let node = LinkedListNode::new(item);
            *node.prev.borrow_mut() = self.tail.clone();
            node
        });

        match &mut self.tail {
            None => {
                self.head = Some(rc_node.clone());
                self.tail = self.head.clone();
            },
            Some(ref mut t) => {
                *t.next.borrow_mut() = Some(rc_node.clone());
                self.tail = Some(rc_node);
            },
        }
        self.size += 1;
    }

    fn pop_front(&mut self) -> Option<T> {
        if let None = self.head {
            return None;
        }

        let temp = self.head.as_ref().unwrap().next.borrow().clone();
        let old_head = self.head.as_ref().unwrap().clone();
        self.head = temp;
        let res = Rc::try_unwrap(old_head).unwrap_err();
        self.size -= 1;

        if self.size == 0 {
            self.tail = None;
        }
        Some(res.element.clone())
    }

    fn remove_at(&mut self, iter: Rc<LinkedListNode<T>>, index: usize) -> bool {
        if self.size == 0 || index >= self.size {
            return false;
        }

        if index == 0 {
            match &*iter.next.borrow() {
                None => {
                    self.head = None;
                    self.tail = None;
                },
                Some(next) => {
                    *next.prev.borrow_mut() = None;
                    self.head = Some(next.clone());
                }
            }
        }

        else if index == self.size - 1 {
            *iter.prev.borrow().as_ref().unwrap().next.borrow_mut() = None;
            self.tail = iter.prev.borrow().clone();
        }

        else {
            *iter.prev.borrow().as_ref().unwrap().next.borrow_mut() = iter.next.borrow().clone();
            *iter.next.borrow().as_ref().unwrap().prev.borrow_mut() = iter.prev.borrow().clone();
        }

        self.size -= 1;
        true
    }

    fn remove(&mut self, node: &T) -> bool {
        if self.size == 0 {
            println!("empty linkedlist");
            return false;
        }

        let mut iter = self.head.clone();
        let mut index: usize = 0;
        while let Some(i) = iter {
            if &i.element == node {
                println!("remove at {}", index);
                return self.remove_at(i.clone(), index);
            }
            iter = i.next.borrow().clone();
            index += 1;
        }
        println!("can't find node {:?}", node);
        false
    }
}

#[derive(Clone, Copy, Debug)]
struct Node {
    key: i32,
    value: i32,
    freq: usize
}

impl PartialEq for Node {
    fn eq(&self, other: &Self) -> bool {
        if self.key == other.key {
            true
        } else {
            false
        }
    }
}

impl Eq for Node {}

impl Node {
    fn new(key: i32, value: i32) -> Self {
        Self {
            key,
            value,
            freq: 1
        }
    }
}

struct LFUCache2 {
    cache: HashMap<i32, Node>,
    freq_map: HashMap<usize, LinkedList<Node>>,
    capacity: usize,
    min_freq: usize
}

impl LFUCache2 {
    pub fn new(capacity: i32) -> Self {
        Self {
            cache: HashMap::new(),
            freq_map: HashMap::new(),
            capacity: capacity as usize,
            min_freq: 1
        }
    }

    fn inc_freq(&mut self, mut node: Node) {
        let size = {
            let ll = self.freq_map.get_mut(&node.freq).unwrap();
            assert!(ll.remove(&node));
            ll.size()
        };

        if size == 0 && node.freq == self.min_freq {
            self.freq_map.remove(&node.freq);
            self.min_freq += 1;
        }

        node.freq += 1;
        match self.freq_map.get_mut(&node.freq) {
            None => {
                let mut ll = LinkedList::<Node>::new();
                ll.push_back(node);
                self.freq_map.insert(node.freq, ll);
            },
            Some(ll) => {
                ll.push_back(node);
            }
        }

        self.cache.insert(node.key, node);
    }

    pub fn get(&mut self, key: i32) -> i32 {
        let mut node = match self.cache.get(&key) {
            None => return -1,
            Some(v) => *v
        };

        self.inc_freq(node);
        node.value
    }

    pub fn put(&mut self, key: i32, value: i32) {
        let mut node = match self.cache.get(&key) {
            None => {
                let new_node = Node::new(key, value);
                
                if self.capacity == 0 {return;}

                if self.cache.len() == self.capacity {
                    let ll_size = {
                        let ll = self.freq_map.get_mut(&self.min_freq).unwrap();
                        let popped_elet = ll.pop_front().unwrap();
                        self.cache.remove(&popped_elet.key);
                        ll.size()
                    };
    
                    if ll_size == 0 {
                        self.freq_map.remove(&self.min_freq);
                    }
                }

                self.min_freq = 1;
                match self.freq_map.get_mut(&1) {
                    None => {
                        self.freq_map.insert(1, {
                            let mut ll = LinkedList::<Node>::new();
                            ll.push_back(new_node);
                            ll
                        });
                    },
                    Some(ll) => {
                        ll.push_back(new_node);
                    }
                }
                self.cache.insert(new_node.key, new_node);
                return;
            },
            Some(node) => {
                *node
            }
        };

        node.value = value;
        self.inc_freq(node);
    }
}

struct LFUCache {
    cache: BTreeSet<Entry>,
    exists: HashMap<i32, Entry>,
    capacity: usize,
    time: u32
}

/*
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl LFUCache {
    fn new(capacity: i32) -> Self {
        Self {
            cache: BTreeSet::new(),
            exists: HashMap::new(),
            capacity: capacity as usize,
            time: 0
        }
    }
    
    fn get(&mut self, key: i32) -> i32 {
        let mut find = match self.exists.get(&key) {
            None => return -1,
            Some(res) => *res
        };

        self.cache.remove(&find);
        self.exists.remove(&key);
        
        find.get_times += 1;
        find.latest_time = self.time;
        self.time += 1;

        self.cache.insert(find);
        self.exists.insert(key, find);

        find.value
    }

    fn shrink(&mut self) {
        let lfu = *self.cache.iter().next().unwrap();
        println!("{} erased", lfu.key);
        self.exists.remove(&lfu.key);
        self.cache.remove(&lfu);
    }
    
    fn put(&mut self, key: i32, value: i32) {
        let mut find = match self.exists.get(&key) {
            None => None,
            Some(res) => Some(*res)
        };
        match find {
            None => {
                if self.cache.len() == self.capacity {
                    self.shrink();
                }
                let new_entry = Entry::new(key, value, self.time);
                self.time += 1;
            
                self.cache.insert(new_entry);
                self.exists.insert(key, new_entry);
            },
            Some(mut entry) => {
                self.cache.remove(&entry);
                self.exists.remove(&entry.key);

                entry.value = value;
                entry.get_times += 1;
                entry.latest_time = self.time;
                self.time += 1;

                self.cache.insert(entry);
                self.exists.insert(key, entry);
            }
        }
    }
}

/*
 * Your LFUCache object will be instantiated and called as such:
 * let obj = LFUCache::new(capacity);
 * let ret_1: i32 = obj.get(key);
 * obj.put(key, value);
 */
fn main() {
    let mut lfu = LFUCache2::new(2);
    lfu.put(1, 1);
    println!("put 1, 1");
    lfu.put(2, 2);
    println!("put 2, 2");
    lfu.put(2, 3);
    println!("put 2, 3");
    lfu.put(4, 4);
    println!("put 4, 4");
    println!("{}", lfu.get(2));
}
