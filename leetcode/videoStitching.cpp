/**********************************************
  > File Name		: videoStitching.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 24 Oct 2020 02:44:46 PM CST
  > Location        : Shanghai
 **********************************************/
#include <iostream>
#include <vector>
using namespace std;

/*
 * Leetcode 1024.视频录制
 * 让我想想
 * 这题应该是要用动态规划做
 * 用dp[i] 表示覆盖区间[0,i]所需要的最少片段数
 * 那么情况就很明朗了
 */

bool compare(vector<int> i, vector<int> j) {
    return i[0] < j[0];
}

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        vector<int> dp(T+1, 0);
        int max = 0;
        //将clips按照起始点进行排序
        std::sort(clips.begin(), clips.end(), compare);
        printVec(clips);
        for (auto& clip: clips) {
            if (clip[0] > max) {
                return -1;
            }
            if (max == T) {
                break;
            }
            if (clip[1] <= max) {
                continue;
            }
            for (int i = max+1; i <= clip[1]; i++) {
                dp[i] = dp[clip[0]] + 1;
                //可能录制超过比赛的时间
                if (i == T) {
                    return dp[T];
                }
            }
            max = clip[1];
        }
        if (max < T) {
            return -1;
        }
        return dp[T];
    }

    void printVec(vector<vector<int>>& vecs) {
        std::cout << "[";
        for (auto vec: vecs) {
            std::cout << "[" << vec[0] << "," << vec[1] << "],";
        }
        std::cout << "]" << std::endl;
    }
}

/*
 * Leetcode 官方解答
 * 这尼玛两个循环都能比我快是没有想到的
 */

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        vector<int> dp(T + 1, INT_MAX - 1);
        dp[0] = 0;
        for (int i = 1; i <= T; i++) {
            for (auto& it : clips) {
                if (it[0] < i && i <= it[1]) {
                    dp[i] = min(dp[i], dp[it[0]] + 1);
                }
            }
        }
        return dp[T] == INT_MAX - 1 ? -1 : dp[T];
    }
};

