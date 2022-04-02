/**********************************************
  > File Name		: Range.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri 01 Apr 2022 04:27:46 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::BTreeSet;

#[derive(Debug, Clone, Copy)]
struct Range {
    left: i32,
    right: i32
}

impl Range {
    fn new(left: i32, right: i32) -> Self {
        Self {
            left,
            right
        }
    }
}

impl std::fmt::Display for Range {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.left, self.right)
    }
}

impl PartialEq for Range {
    fn eq(&self, other: &Self) -> bool {
        self.left == other.left
    }
}

impl Eq for Range {}

impl PartialOrd for Range {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.left.cmp(&other.left))
    }
}

impl Ord for Range {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.partial_cmp(other).unwrap()
    }
}

struct RangeModule {
    ranges: BTreeSet<Range>
}

impl RangeModule {
    fn new() -> Self {
        Self {
            ranges: {
                let mut ranges = BTreeSet::<Range>::new();
                ranges.insert(Range::new(-1, 0));
                ranges
            }
        }
    }

    //fn check(x: &Range) -> bool {
        //if x.left <= 0 {return false;}
        //if x.right > left {
            //println!("{} on the left", x);
            //return true;
        //}
        //if x.left < right {
            //println!("{} on the right", x);
            //return true;
        //}
        //false
    //}

    pub fn add_range(&mut self, left: i32, right: i32) {
        if self.ranges.len() == 1 {
            self.ranges.insert(Range::new(left, right));
        print!("add range({}, {}): ", left, right); self.show_ranges();
            return;
        }

        //println!("ranges: {:?}", self.ranges);

        let delete = self.ranges.iter().
            filter(|x| x.left > 0 && ((x.left < left && x.right >= left) || (x.left <= right && x.right > right) || (x.left >= left && x.right <= right))).
            //filter(|x| check).
            map(|x| *x).collect::<Vec<Range>>();

        let mut new_range = Range::new(left, right);

        println!("delete: {:?}", delete);

        if delete.is_empty() {
            self.ranges.insert(new_range);
        print!("add range({}, {}): ", left, right); self.show_ranges();
            return;
        }
        
        for r in delete.iter() {
            assert!(self.ranges.remove(r));
        }

        if delete[0].left < left {
            new_range.left = delete[0].left;
        }

        if delete[delete.len() - 1].right > right {
            new_range.right = delete[delete.len() - 1].right;
        }

        self.ranges.insert(new_range);

        print!("add range({}, {}): ", left, right); self.show_ranges();
    }

    fn remove_range(&mut self, left: i32, right: i32) {
        if self.ranges.len() == 1 {
            return;
        }

        let delete = self.ranges.iter().
            filter(|x| x.left > 0 && ((x.left < left && x.right > left) || (x.left < right && x.right > right) || (x.left >= left && x.right <= right))).
            map(|x| *x).collect::<Vec<Range>>();

        if delete.is_empty() {
            println!("remove range({}, {}) failed", left, right);
            return;
        }

        for r in delete.iter() {
            assert!(self.ranges.remove(r));
        }

        if delete[0].left < left {
            self.ranges.insert(Range::new(delete[0].left, left));
        }

        if delete[delete.len() - 1].right > right {
            self.ranges.insert(Range::new(right, delete[delete.len() - 1].right));
        }

        //println!("{:?}", self.ranges);

        print!("remove range({}, {}): ", left, right); self.show_ranges();
    }

    fn query_range(&self, left: i32, right: i32) -> bool {
        if self.ranges.len() == 1 {
            return false;
        }

        let query_size = self.ranges.iter().filter(|x| x.left <= left && x.right >= right).fold(0 as usize, |acc, x| acc+1);

        println!("query range({}, {}): {}", left, right, query_size == 1);
        query_size == 1
    }

    fn show_ranges(&self) {
        let mut iter = self.ranges.iter();
        iter.next();

        print!("[");
        while let Some(i) = iter.next() {
            print!("{}, ", i);
        }
        println!("]");
    }
}

fn main() {
    let mut rm = RangeModule::new();
    rm.add_range(6, 8);
    rm.remove_range(7, 8);
    rm.remove_range(8, 9);
    rm.add_range(8, 9);
    rm.remove_range(1, 3);
    rm.add_range(1, 8);
    rm.query_range(2, 4);
    rm.query_range(2, 9);
    rm.query_range(4, 6);
}
