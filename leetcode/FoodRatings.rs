/**********************************************
  > File Name		: FoodRatings.rs
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat Jul 30 11:43:50 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

use std::collections::{HashMap, BTreeSet};
use std::cell::RefCell;

#[derive(PartialEq, Eq)]
struct Node {
    food: String,
    rating: RefCell<i32>
}

impl Node {
    fn new(food: String, rating: i32) -> Self {
        Self {
            food,
            rating: RefCell::new(rating)
        }
    }
}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        if self.rating == other.rating {
            self.food.cmp(&other.food)
        } else {
            other.rating.cmp(&self.rating)
        }
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

struct FoodRatings {
    cuisine_node: HashMap<String, BTreeSet<Node>>,
    food_info: HashMap<String, (String, i32)>,
}


/*
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl FoodRatings {

    fn new(foods: Vec<String>, cuisines: Vec<String>, ratings: Vec<i32>) -> Self {
        let n = foods.len();
        let mut cuisine_node = HashMap::<String, BTreeSet<Node>>::new();
        let mut food_info = HashMap::<String, (String, i32)>::with_capacity(n);

        for i in 0..n {
            let food = &foods[i];
            match cuisine_node.get_mut(&cuisines[i]) {
                Some(set) => {
                    set.insert(Node::new(food.clone(), ratings[i]));
                },
                None => {
                    let mut s = BTreeSet::<Node>::new();
                    s.insert(Node::new(food.clone(), ratings[i]));
                    cuisine_node.insert(cuisines[i].clone(), s);
                }
            }
            food_info.insert(food.clone(), (cuisines[i].clone(), ratings[i]));
        }

        Self {
            cuisine_node,
            food_info
        }
    }
    
    fn change_rating(&mut self, food: String, new_rating: i32) {
        let (cuisine, old_rating) = self.food_info.get(&food).unwrap();
        if let Some(set) = self.cuisine_node.get_mut(cuisine) {
            assert!(set.remove(&Node::new(food.clone(), *old_rating)));
            set.insert(Node::new(food.clone(), new_rating));
        }

        //self.food_rating[&food] = new_rating;
        self.food_rating.insert(food, new_rating);
    }
    
    fn highest_rated(&self, cuisine: String) -> String {
        //*self.cuisine_node.get(&cuisine).unwrap().first().unwrap()
        let set = self.cuisine_node.get(&cuisine).unwrap();
        let mut iter = set.iter();
        iter.next().unwrap().food.clone()
    }
}

/*
 * Your FoodRatings object will be instantiated and called as such:
 * let obj = FoodRatings::new(foods, cuisines, ratings);
 * obj.change_rating(food, newRating);
 * let ret_2: String = obj.highest_rated(cuisine);
 */
fn main() {}
