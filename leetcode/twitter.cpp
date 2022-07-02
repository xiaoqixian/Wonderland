/**********************************************
  > File Name		: twitter.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Mon 13 Dec 2021 01:17:14 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <queue>
using namespace std;

class Compare {
public:
    bool operator()(pair<unsigned int, int> p1, pair<unsigned int, int> p2) {
        return p1.first < p2.first;
    }
};

class Twitter {
private:
    unordered_map<int, vector<pair<unsigned int, int>>> tweets;
    //unordered_map<int, pq> tweets;//tweets posted by user
    unordered_map<int, vector<int>> followers;
    unordered_map<int, vector<int>>::iterator f_iter;
    unordered_map<int, vector<pair<unsigned int, int>>>::iterator t_iter;
    unsigned int time;
public:
    Twitter() {
        this->time = 0;
    }
    
    void postTweet(int userId, int tweetId) {
        this->t_iter = this->tweets.find(userId);
        if (this->t_iter == this->tweets.end()) {
            this->tweets[userId] = {make_pair(this->time, tweetId)};
        } else {
            this->t_iter->second.push_back(make_pair(this->time, tweetId));
        }
        this->time++;
    }
    
    vector<int> getNewsFeed(int userId) {
        this->f_iter = this->followers.find(userId);
        if (this->f_iter == this->followers.end()) {
            this->followers[userId] = {userId};
            this->f_iter = this->followers.find(userId);
        }
        
        vector<int> res;
        vector<int>& fls = this->f_iter->second;
        priority_queue<pair<unsigned int, int>, vector<pair<unsigned int, int>>, Compare> pq;
        for (int uid: fls) {
            if (uid == -1) {
                continue;
            }

            this->t_iter = this->tweets.find(uid);
            if (this->t_iter == this->tweets.end()) {
                continue;//this user has not posted any tweet yet.
            }
            
            vector<pair<unsigned int, int>>& tts = this->t_iter->second;
            int s = tts.size();
            for (int i = 0; i < 10 && i < s; i++) {
                pq.push(tts[s-i-1]);
            }
        }
        
        while (!pq.empty() && res.size() < 10) {
            pair<unsigned int, int> p = pq.top();
            res.push_back(p.second);
            pq.pop();
        }
        return res;
    }
    
    void follow(int followerId, int followeeId) {
        this->f_iter = this->followers.find(followerId);
        if (this->f_iter == this->followers.end()) {
            this->followers[followerId] = {followerId, followeeId};
            return;
        }
        vector<int>& fls = this->f_iter->second;
        int s = fls.size();
        for (int i = 0; i < s; i++) {
            if (fls[i] == followeeId) {//already followed
                return;
            }
        }
        this->f_iter->second.push_back(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        this->f_iter = this->followers.find(followerId);
        if (this->f_iter == this->followers.end()) {
            return;
        }
        
        vector<int>& fls = this->f_iter->second;
        int s = fls.size();
        for (int i = 0; i < s; i++) {
            if (fls[i] == followeeId) {
                fls[i] = -1;
                return;
            }
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

void printv(vector<int>& v) {
    printf("[");
    if (v.size() == 0) {
        printf("]\n");
        return;
    } else {
        printf("%d", v[0]);
    }
    for (int i = 1; i < v.size(); i++) {
        printf(", %d", v[i]);
    }
    printf("]\n");
}

int main() {
    Twitter* t = new Twitter();
    t->postTweet(1, 5);
    auto v = t->getNewsFeed(1);
    printv(v);
    t->follow(1, 2);
    t->postTweet(2, 6);
    v = t->getNewsFeed(1);
    printv(v);
    t->unfollow(1, 2);
    v = t->getNewsFeed(1);
    printv(v);
}
