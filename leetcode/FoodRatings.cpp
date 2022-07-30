/**********************************************
  > File Name		: FoodRatings.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Fri Jul 29 20:30:09 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
using namespace std;

class FoodRatings {
private:
    struct Node {
        const string food;
        int rating;

        Node() {}
        Node(string food, int rating): food(food), rating(rating) {}

        bool operator()(const Node& n1, const Node& n2) const {
            if (n1.rating == n2.rating) {
                return n1.food < n2.food;
            } else return n1.rating > n2.rating;
        }
    };

    unordered_map<string, set<Node, Node>> cuisine_node;
    unordered_map<string, string> food_cuisine;
    unordered_map<string, int> food_rating;

public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        const int n = foods.size();
        for (int i = 0; i < n; i++) {
            auto it = this->cuisine_node.find(cuisines[i]);
            auto new_node = Node(foods[i], ratings[i]);

            if (it == this->cuisine_node.end()) {
                set<Node, Node> s;
                s.insert(std::move(new_node));
                this->cuisine_node.insert({cuisines[i], std::move(s)});
            } else {
                it->second.insert(std::move(new_node));
            }

            this->food_cuisine.insert({foods[i], cuisines[i]});
            this->food_rating.insert({foods[i], ratings[i]});
        }
    }
    
    void changeRating(const string& food, int newRating) {
        const string& cuisine = this->food_cuisine[food];
        auto& cuisine_nodes = this->cuisine_node.find(cuisine)->second;
        const auto& it = cuisine_nodes.find(Node(food, this->food_rating[food]));
        cuisine_nodes.erase(it);
        cuisine_nodes.insert(Node(food, newRating));
        this->food_rating[food] = newRating;
    }
    
    string highestRated(const string& cuisine) {
        return this->cuisine_node.find(cuisine)->second.begin()->food;
    }
};

int main() {}

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */
