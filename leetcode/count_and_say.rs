struct Solution {}
/*
impl Solution {
    pub fn count_and_say(n: i32) -> String {
        if n == 1 {
            return String::from("1");
        } else {
            let last = count_and_say(n-1).as_bytes();//seems rust doesn't support traversal call.
            let res: String = String::from("");
            let mut temp = 'c';
            let mut count: i16 = 0;
            for (i, &item) in last.iter().enumerate() {
                if temp == 'c' {
                    temp = item;
                    count += 1;
                    continue;
                }
                if item != temp {
                    res.push_str(count);
                    res.push_str(item);
                    count += 1;
                    temp = item;
                } else {
                    count += 1;
                }
            }
            return res;
        }
    }
}
*/
fn count(n: i32) -> String {
    if n == 1 {
        return String::from("1");
    } else {
        let last = count(n-1).as_bytes();//seems rust doesn't support traversal call.
        let res: String = String::from("");
        let mut temp: u8 = 0;
        let mut count: i16 = 0;
        for (i, &item) in last.iter().enumerate() {
            if temp == 0 {
                temp = item;
                count += 1;
                continue;
            }
            if item != temp {
                res.push_str(String::from(count));
                res.push(item);
                count += 1;
                temp = item;
            } else {
                count += 1;
            }
        }
        return res;
    }
}

fn main() {
    count(5);
}
