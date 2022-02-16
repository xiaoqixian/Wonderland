/**********************************************
  > File Name		: map.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 15 Feb 2022 10:09:11 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

mod tree_map;

trait Map<K, V> where K: Ord {
    fn get<'a>(&'a self, k: &K) -> Option<&'a V>;

    fn get_mut<'a>(&'a mut self, k: &K) -> Option<&'a mut V>;

    fn insert(&mut self, k: K, v: V) -> Option<V>;

    fn remove(&mut self, k: &K) -> Option<V>;
}
