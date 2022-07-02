/**********************************************
  > File Name		: temp.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 09 Apr 2022 08:26:04 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

struct T {
    val: i32
}

fn main() {
    let mut s = std::collections::BTreeSet::<T>::new();
    s.insert(T {val: -1});
}
