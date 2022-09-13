/**********************************************
  > File Name		: most_booked.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Sep  4 17:16:40 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

trait Comp<T> {
    fn comp(&self, p2: &T) -> bool; //return true if self < p2.
}

struct PriorityQueue<T: Copy+Comp<T>> {
    queue: Vec<T>,
    alloc: usize //number of elements in queue
}

impl<T> PriorityQueue<T> where T: Copy+Comp<T> {
    fn new() -> Self {
        Self {
            queue: Vec::new(),
            alloc: 0
        }
    }

    fn size(&self) -> usize {
        self.alloc
    }

    fn empty(&self) -> bool {
        self.alloc == 0
    }

    fn exch(&mut self, i: usize, j: usize) {
        let temp = self.queue[i];
        self.queue[i] = self.queue[j];
        self.queue[j] = temp;
    }

    fn swim(&mut self, mut k: usize) {
        while k > 1 && self.queue[k].comp(&self.queue[k/2]) {
            self.exch(k, k/2);
            k /= 2;
        }
    }

    fn sink(&mut self, mut k: usize) -> usize {
        let mut j: usize;
        let size = self.alloc;
        
        while 2*k <= size {
            j = 2*k;
            if j < size && self.queue[j+1].comp(&self.queue[j]) {
                j += 1;
            }
            if !self.queue[j].comp(&self.queue[k]) {
                break;
            }
            self.exch(j, k);
            k = j;
        }
        k
    }

    fn pop(&mut self) -> Option<T> {
        if self.alloc == 0 {
            return None;
        }
        
        let res = Some(self.queue[1]);
        self.exch(1, self.alloc);
        self.alloc -= 1;
        self.sink(1);
        res
    }

    fn push(&mut self, item: T) {
        if self.queue.len() == 0 {
            self.queue.push(item);//queue[0] is not used.
        }
        if self.alloc == self.queue.len()-1 {
            self.queue.push(item);
            self.alloc += 1;
        } else {
            self.alloc += 1;
            self.queue[self.alloc] = item;
        }
        self.swim(self.alloc);
    }
}

type Room = (u64, u64, i32);

impl Comp<Room> for Room {
    fn comp(&self, p2: &Room) -> bool {
        if self.1 == p2.1 {
            self.2 > p2.2
        } else {
            self.1 > p2.1
        }
    }
}

struct Solution;

impl Solution {
    pub fn most_booked(n: i32, mut meetings: Vec<Vec<i32>>) -> i32 {
        meetings.sort_by(|v1, v2| {v1[0] < v2[0]});

        
    }
}
