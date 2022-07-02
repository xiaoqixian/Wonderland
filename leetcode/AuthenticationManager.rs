/**********************************************
  > File Name		: AuthenticationManager.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 13 Feb 2022 06:28:17 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::HashMap;

struct AuthenticationManager {
    inner: HashMap<String, i32>,
    time_to_live: i32
}


/*
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl AuthenticationManager {

    fn new(time_to_live: i32) -> Self {
        Self {
            inner: HashMap::new(),
            time_to_live
        }
    }
    
    fn generate(&mut self, token_id: String, current_time: i32) {
        self.inner.insert(token_id, current_time + self.time_to_live);
    }
    
    fn renew(&mut self, token_id: String, current_time: i32) {
        match self.inner.get_mut(&token_id) {
            None => (),
            Some(expire_time) => {
                if (*expire_time > current_time) {
                    *expire_time = self.time_to_live + current_time;
                }
            }
        }
    }
    
    fn count_unexpired_tokens(&self, current_time: i32) -> i32 {
        let mut res = 0;
        for (_, expire_time) in self.inner.into_iter() {
            if expire_time > current_time {
                res += 1;
            }
        }
        res
    }
}

/*
 * Your AuthenticationManager object will be instantiated and called as such:
 * let obj = AuthenticationManager::new(time_to_live);
 * obj.generate(tokenId, currentTime);
 * obj.renew(tokenId, currentTime);
 * let ret_3: i32 = obj.count_unexpired_tokens(currentTime);
 */
