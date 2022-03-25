/**********************************************
  > File Name		: LFUCache.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 25 Mar 2022 02:42:14 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::{HashMap, BTreeSet};

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
    let mut lfu = LFUCache::new(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    lfu.get(1);
    lfu.put(3, 3);
    println!("{}", lfu.get(2));
}
