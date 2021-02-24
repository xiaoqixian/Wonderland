/**********************************************
  > File Name		: extensive_hash_table.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 24 Feb 2021 09:00:06 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::ptr::NonNull;

struct Record {
    key: u32,
    s: String
}

impl Record {
    pub fn new(key: u32, s: String) -> Self {
        Record {
            key,
            s,
        }
    }
}

struct Block {
    j: i32,
    records: [Option<NonNull<Record>>; 4]
}

impl Block {
    pub fn new() -> Self {
        Block {
            j: 1,
            records: [None, None, None, None]
        }
    }
}

struct ExtensiveHashTable {
    i: i32,
    bucket_array: Vec<Option<NonNull<Block>>>
}

impl ExtensiveHashTable {
    fn hash(&self, mut key: u32) -> u32 {
        if key < 1<<4 {

        } else if key < 1<<8 {
            let mut low_4_bits = key & 0x0000000f;
            key >>= 4;
            low_4_bits <<= 4;
            key |= low_4_bits;
        } else if key < 1<<16 {
            let mut low_8_bits = key & 0x000000ff;
            key >>= 8;
            low_8_bits <<= 8;
            key |= low_8_bits;
        } else {
            let mut low_16_bits = key & 0x0000ffff;
            key >>= 16;
            low_16_bits <<= 16;
            key |= low_16_bits;
        }
        key
    }

    fn expand(&mut self) {
        if self.i >= 32 {
            println!("Buckets array length out of bounds.");
            return ;
        }
        let mut temp: Vec<Option<NonNull<Block>>> = Vec::with_capacity(1<<(self.i+1));
        temp.resize(1<<(self.i+1), None);
        let mut k = 0;
        let mut p = 0;
        self.i += 1;
        while k < 1<<self.i {
            let j:i32 = unsafe {
                (*self.bucket_array[p].unwrap().as_ptr()).j
            };
            for m in 0..(1<<(self.i-j)) {
                temp[k+m] = self.bucket_array[p].clone();
            }
            k += 1<<self.i-j;
            p += 1<<self.i-j-1;
        }
        self.bucket_array = temp;
    }

    /*
     * When we need to split a block, the block may be connected by multiple
     * pointers, and we need to have part of them point to a new block.
     */
    fn adjust_new_block(&mut self, old_block: Option<NonNull<Block>>, new_block: Option<NonNull<Block>>, location: i32) {
        let j = unsafe {
            (*old_block.unwrap().as_ptr()).j
        };
        let mut count = self.i + j + 1;
        let mut k = 0;
        let mut up = 0;
        let mut temp = location;
        while count > 0 {
            let low_1_bit = location & 0x00000001;
            if low_1_bit != 0 {
                up += 1<<k;
            }
            k += 1;
            location >>= 1;
            count -= 1;
        }
        let start = temp - up + 1<<self.i-j;
        if start < 0 {
            println!("Adjust new block error.");
            assert!(false);
        }
        for k in 0..(1<<self.i-j) {
            self.bucket_array[start + k] = new_block.clone();
        }
    }
}

fn main() {
    
}
