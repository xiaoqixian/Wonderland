/**********************************************
  > File Name		: circular_queue.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 14 Dec 2021 10:05:05 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

struct MyCircularQueue {
    cq: Vec<i32>,
    head: usize,
    tail: usize,
    alloc: usize
}


/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl MyCircularQueue {

    fn new(k: i32) -> Self {
        Self {
            cq: vec![0; k as usize],
            head: 0,
            tail: 0,
            alloc: 0
        }
    }
    
    fn en_queue(&mut self, value: i32) -> bool {
        if self.alloc == self.cq.len() {
            return false;
        }
        self.cq[self.tail] = value;
        self.tail += 1;
        self.alloc += 1;
        if self.tail == self.cq.len() {
            self.tail = 0;
        }
        true
    }
    
    fn de_queue(&mut self) -> bool {
        if self.alloc == 0 {
            return false;
        }
        self.head += 1;
        self.alloc -= 1;
        if self.head == self.cq.len() {
            self.head = 0;
        }
        true
    }
    
    fn front(&self) -> i32 {
        if self.alloc == 0 {
            -1
        } else {
            self.cq[self.head]
        }
    }
    
    fn rear(&self) -> i32 {
        if self.alloc == 0 {
            -1
        } else {
            if self.tail == 0 {
                self.cq[self.cq.len()-1]
            } else {
                self.cq[self.tail-1]
            }
        }
    }
    
    fn is_empty(&self) -> bool {
        self.alloc == 0
    }
    
    fn is_full(&self) -> bool {
        self.alloc == self.cq.len()
    }
}

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * let obj = MyCircularQueue::new(k);
 * let ret_1: bool = obj.en_queue(value);
 * let ret_2: bool = obj.de_queue();
 * let ret_3: i32 = obj.front();
 * let ret_4: i32 = obj.rear();
 * let ret_5: bool = obj.is_empty();
 * let ret_6: bool = obj.is_full();
 */
