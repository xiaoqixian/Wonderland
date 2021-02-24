/**********************************************
  > File Name		: extensive_hash_table.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 24 Feb 2021 08:15:01 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::fmt::Display;
use std::cmp::Ord;

struct Record<T, K> where T: Display + Ord {
    key: T,
    data: K
}

impl<T, K> Record<T,K> where T: Display + Ord {
    pub fn new(key: T, data: K) -> Self {
        Record {
            key,
            data
        }
    }
}

/* In our case, 4 reocrd pointers per block.*/
struct Block<T, K> where T: Display + Ord {
    j: u32,
    records: Vec<Option<Box<Record<T, K>>>>
}

impl<T, K> Block<T, K> where T: Display + Ord {
    pub fn new() -> Self {
        Block {
            j: 1,
            records: [None; 4].to_vec(),
        }
    }
}

struct ExtensiveHashTable<T, K> where T: Display + Ord {
    i: u32,
    bucket_array: Vec<Option<Box<Block<T, K>>>>
}

impl<T, K> ExtensiveHashTable<T, K> where T: Display + Ord {

}

fn main() {

}
