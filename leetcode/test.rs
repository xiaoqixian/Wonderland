// Date: Thu Aug 31 16:18:06 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

use std::cell::RefCell;

fn main() {
    let a: Vec<RefCell<bool>> = vec![RefCell::new(false); 5];

    if !*a[1].borrow() {
        a[1].replace(true);
    }

    println!("{}", *a[1].borrow());
}
