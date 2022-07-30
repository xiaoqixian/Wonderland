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
    fn adjust_new_block(&mut self, old_block: Option<NonNull<Block>>, new_block: Option<NonNull<Block>>, mut location: i32) {
        let j = unsafe {
            (*old_block.unwrap().as_ptr()).j
        };
        let mut count = self.i + j + 1;
        let mut k = 0;
        let mut up = 0;
        let temp = location;
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
            self.bucket_array[(start + k) as usize] = new_block.clone();
        }
    }

    fn find_location(&self, key: u32) -> u32 {
        let hashed_key = self.hash(key);
        let hash_val = hashed_key >> (32-self.i);
        if hash_val >= (1<<self.i) {
            println!("Hash value error.");
            assert!(false);
        }
        hash_val
    }

    fn find_block(&self, key: u32) -> Option<NonNull<Block>> {
        let hash_val = self.find_location(key);
        let p = self.bucket_array[hash_val as usize].clone();
        match &p {
            None => {
                println!("No such record with key = {}", key);
                None
            },
            Some(_) => {
                p
            }
        }
    }

    pub fn new() -> Self {
        ExtensiveHashTable {
            i: 1,
            bucket_array: {
                let mut b = Vec::with_capacity(2);
                b.resize(2, Some(unsafe {NonNull::new_unchecked(Box::into_raw(Box::new(Block::new())))}));
                b
            }
        }
    }

    fn search(&self, key: u32, mut b: Option<NonNull<Block>>) -> Option<NonNull<Record>> {
        if let None = b {
            b = self.find_block(key);
        }
        if let None = b {
            return None;
        }
        let records = unsafe {
            (*b.unwrap().as_ptr()).records
        };
        for record in records.iter() {
            if let Some(r) = record {
                if key == unsafe {(*r.as_ptr()).key} {
                    println!("Found record with key = {}", key);
                    return *record;
                }
            }
        }
        None
    }

    pub fn insert_record(&mut self, r: Option<NonNull<Record>>) {
        if let None = r {
            println!("Can't insert a None record!");
            return;
        }
        let key = unsafe {
            (*r.unwrap().as_ptr()).key
        };
        let b = self.find_block(key);
        if let None = b {
            panic!("Exists NULL pointer in the bucket array");
        }
        if let Some(_) = self.search(key, b) {
            println!("Key duplicated, insertion terminated");
            return ;
        }
        let records = &mut unsafe {
            (*b.unwrap().as_ptr()).records
        };
        for k in 0..4 {
            if let None = records[k] {
                records[k] = r;
                println!("Successfully inserted a record with key = {} in block {}", key, self.find_location(key));
                return ;
            }
        }
        /*
         * No space in the current block.
         */
        let mut j = unsafe {
            (*b.unwrap().as_ptr()).j
        };
        if j == self.i {
            println!("Need to expand the bucket array.");
            self.expand();
        }
        let hash_val = self.find_location(key);
        if (j < self.i) {
            j += 1;
            let mut new_block = Some(unsafe {NonNull::new_unchecked(Box::into_raw(Box::new(Block::new())))});
            unsafe {
                (*new_block.unwrap().as_ptr()).j = j;
                (*b.unwrap().as_ptr()).j = j;
            }
            self.adjust_new_block(b, new_block, hash_val as i32);
            /* 
             * Now we need to distribute the attributes in the old block into 
             * two blocks.
             */
            let mut temp = 0;//temp count for records moved to the new block.
            let new_block_records = &mut unsafe {
                (*new_block.unwrap().as_ptr()).records
            };
            for k in 0..4 {
                if let None = records[k] {
                    continue;
                }
                /*
                 * number j in the binary sequences decides which block to go
                 */
                let re_key = unsafe {
                    (*records[k].unwrap().as_ptr()).key
                };
                let hashed_key = self.hash(re_key);
                let d = hashed_key >> (j-1);
                if d & 0x1 == 0 {
                    println!("{} stays the same.", re_key);
                    continue;
                } else {
                    new_block_records[temp] = records[k].clone();
                    records[k] = None;
                    println!("{} moved to the new block.", re_key);
                }
            }
            /* If all of the pointers go to one of the blocks.*/
            if temp == 0 || temp == 4 {
                println!("All records go to one of the blocks.");
                self.insert_record(r);
            } else {
                let hashed_key = self.hash(key);
                let d = hashed_key >> (j-1);
                if d & 0x1 == 0 {
                    for k in 0..4 {
                        if let None = records[k] {
                            records[k] = r.clone();
                            println!("Successfully inserted a record with key = {} in block {}", key, self.find_location(key));
                            return ;
                        }
                    }
                } else {
                    new_block_records[temp] = r.clone();
                    println!("Successfully inserted a record with key = {} in block {}", key, self.find_location(key));
                }
            }
        }
    }
}

fn main() {
    
}
