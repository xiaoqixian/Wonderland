/**********************************************
  > File Name		: flip_and_invert_image.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 24 Feb 2021 10:40:58 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

impl Solution {
    pub fn flip_and_invert_image(a: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut res = Vec::new();
        let len = a[0].len();
        //println!("len = {}", len);
        for row in a {
            let mut new_row: Vec<i32> = row.clone();
            for i in 0..(len/2) {
                if row[i] ^ row[len-i-1] == 1 {
                    continue;
                } else {
                    new_row[i] = row[i] ^ 1;
                    new_row[len-i-1] = new_row[i];
                }
            }
            if len % 2 == 1 {
                new_row[len/2] ^= 1;
            }
            res.push(new_row);
        }
        res
    }
}
