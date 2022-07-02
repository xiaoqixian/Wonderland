/**********************************************
  > File Name		: DinnerPlates.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 03 Apr 2022 11:18:30 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::BTreeSet;

struct DinnerPlates {
    capacity: usize,
    plates: Vec<Vec<i32>>,
    remain: BTreeSet<usize>,
    nonempty: BTreeSet<usize>
}


/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl DinnerPlates {

    fn new(capacity: i32) -> Self {
        Self {
            capacity: capacity as usize,
            plates: Vec::new(),
            remain: BTreeSet::new(),
            nonempty: BTreeSet::new()
        }
    }
    
    fn push(&mut self, val: i32) {
        if self.remain.is_empty() {
            self.plates.push(vec![val]);
            let size = self.plates.len();
            
            self.nonempty.insert(size-1);
            if self.capacity > 1 {
                self.remain.insert(size-1);
            }
        } else {
            let min_remain: usize = *self.remain.iter().min().unwrap();
            let stack_size = {
                let s = &mut self.plates[min_remain];
                s.push(val);
                s.len()
            };
            
            if stack_size == self.capacity {
                self.remain.remove(&min_remain);
            }

            if stack_size == 1 {
                self.nonempty.insert(min_remain);
            }
        }
    }
    
    fn pop(&mut self) -> i32 {
        if self.nonempty.is_empty() {
            return -1;
        }

        let max_nonempty: usize = *self.nonempty.iter().max().unwrap();
        let (res, stack_size) = {
            let s = &mut self.plates[max_nonempty];
            (s.pop().unwrap(), s.len())
        };

        if stack_size == self.capacity-1 {
            self.remain.insert(max_nonempty);
        }

        if stack_size == 0 {
            self.nonempty.remove(&max_nonempty);
        }
        res
    }
    
    fn pop_at_stack(&mut self, i: i32) -> i32 {
        let index = i as usize;
        if self.nonempty.is_empty() || index >= self.plates.len() {
            return -1;
        }

        let (res, stack_size) = {
            let s = &mut self.plates[index];
            if s.is_empty() {
                return -1;
            }
            (s.pop().unwrap(), s.len())
        };

        if stack_size == self.capacity-1 {
            self.remain.insert(index);
        }

        if stack_size == 0 {
            self.nonempty.remove(&index);
        }

        res
    }
}

fn main() {
    let mut a = BTreeSet::new();
    a.insert(5); a.insert(2); a.insert(7); a.insert(1);
    println!("{:?}", a.iter().max().unwrap());
}

/*
 * Your DinnerPlates object will be instantiated and called as such:
 * let obj = DinnerPlates::new(capacity);
 * obj.push(val);
 * let ret_2: i32 = obj.pop();
 * let ret_3: i32 = obj.pop_at_stack(index);
 */
