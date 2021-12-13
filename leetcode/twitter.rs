/**********************************************
  > File Name		: twitter.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 13 Dec 2021 07:12:00 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::HashMap;

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

    fn swim(&mut self, kk: usize) {
        let mut k = kk;
        while k > 1 && self.queue[k].comp(&self.queue[k/2]) {
            self.exch(k, k/2);
            k /= 2;
        }
    }

    fn sink(&mut self, kk: usize) -> usize {
        let mut j: usize;
        let mut k = kk;
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
        return k;
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

type Pair = (u32, i32);

impl PriorityQueue<Pair> {
    fn print_with_priority(&self) {
        print!("[");
        for i in 1..self.alloc+1 {
            print!("[{}, {}], ", self.queue[i].0, self.queue[i].1);
        }
        println!("]");
    }
}

impl Comp<Pair> for Pair {
    fn comp(&self, p2: &Pair) -> bool {
        self.0 > p2.0
    }
}

struct Twitter {
    tweets: HashMap<i32, Vec<(u32, i32)>>,
    followers: HashMap<i32, Vec<i32>>,
    time: u32
}

/**
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl Twitter {

    fn new() -> Self {
        Self {
            tweets: HashMap::new(),
            followers: HashMap::new(),
            time: 0
        }
    }
    
    fn post_tweet(&mut self, user_id: i32, tweet_id: i32) {
        match self.tweets.get_mut(&user_id) {
            None => {
                self.tweets.insert(user_id, vec![(self.time, tweet_id)]);
            },
            Some(v) => {
                v.push((self.time, tweet_id));
            }
        };
        self.time += 1;
    }
    
    fn get_news_feed(&mut self, user_id: i32) -> Vec<i32> {
        let fls = match self.followers.get(&user_id) {
            None => {
                self.followers.insert(user_id, vec![user_id]);
                self.followers.get(&user_id).unwrap()
            },
            Some(v) => v
        };
        
        let mut res = Vec::new();
        let mut pq: PriorityQueue<Pair> = PriorityQueue::new();

        for uid in fls.iter() {
            if *uid == -1 {
                continue;
            }
            
            let tts: &Vec<(u32, i32)> = match self.tweets.get(uid) {
                None => {
                    continue;
                },
                Some(v) => v
            };
            
            let s = if tts.len() > 10 {
                10
            } else {
                tts.len()
            };
            let len = tts.len();
            for i in 0..s {
                pq.push(tts[len-i-1]);
            }
        }

        while !pq.empty() && res.len() < 10 {
            res.push(pq.pop().unwrap().1);
        }
        return res;
    }
    
    fn follow(&mut self, follower_id: i32, followee_id: i32) {
        let fls = match self.followers.get_mut(&follower_id) {
            None => {
                self.followers.insert(follower_id, vec![follower_id, followee_id]);
                return;
            },
            Some(v) => v
        };
        
        for i in 0..fls.len() {
            if fls[i] == followee_id {
                return;
            }
        }

        fls.push(followee_id);
    }
    
    fn unfollow(&mut self, follower_id: i32, followee_id: i32) {
        let fls = match self.followers.get_mut(&follower_id) {
            None => {
                return;
            },
            Some(v) => v
        };
        
        for i in 0..fls.len() {
            if fls[i] == followee_id {
                fls[i] = -1;
                return;
            }
        }
    }
}


/*
 * Your Twitter object will be instantiated and called as such:
 * let obj = Twitter::new();
 * obj.post_tweet(userId, tweetId);
 * let ret_2: Vec<i32> = obj.get_news_feed(userId);
 * obj.follow(followerId, followeeId);
 * obj.unfollow(followerId, followeeId);
 */
fn main() {
    let mut t = Twitter::new();
    t.post_tweet(1, 5);
    println!("{:?}", t.get_news_feed(1));
    t.follow(1, 2);
    t.post_tweet(2, 6);
    println!("{:?}", t.get_news_feed(1));
    t.unfollow(1, 2);
    println!("{:?}", t.get_news_feed(1));
}
