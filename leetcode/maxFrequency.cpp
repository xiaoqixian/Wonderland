/**********************************************
  > File Name		: maxFrequency.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Tue 20 Jul 2021 12:01:44 AM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <stdio.h>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
     * Solution1
     * O(n^2) time complexity
     */
    int maxFrequency1(vector<int>& nums, int k) {
        if (nums.size() <= 1) {
            return (int)nums.size();
        }
        std::sort(nums.begin(), nums.end());
        int res = 0;
        int ele = nums[0];
        for (int i = 0; i < nums.size(); i++) {
            if (i < nums.size() && nums[i] == nums[i+1]) {
                continue;
            }
            int money = k;
            int j = i;
            int count = 0;
            while (money >= 0 && j >= 0) {
                money -= (nums[i] - nums[j--]);
                if (money >= 0) {
                    count += 1;
                }
            }
            if (count > res) {
                res = count;
            }
        }
        return res;
    }

    /*
     * Solution2
     * Using queue
     */
    int maxFrequency2(vector<int>& nums, int k) {
        if (nums.size() <= 1) {
            return (int)nums.size();
        }
        std::sort(nums.begin(), nums.end());
        std::queue<int> q;
        int res = 0;
        long long q_sum = 0;

        for (int i = 0; i < nums.size(); i++) {
            q.push(nums[i]);
            q_sum += nums[i];
            if (i < nums.size()-1 && nums[i] == nums[i+1]) {
                continue;
            }

            while (q.size()*nums[i] - q_sum > k) {
                q_sum -= q.front();
                q.pop();
            }

            //res = q.size() > res ? q.size() : res;
            if (q.size() > res) {
                res = q.size();
                printf("num = %d, max = %d\n", nums[i], res);
            }
        }
        return res;
    }

    /*
     * Solution3
     * Using queue and map
     */
    int maxFrequency3(vector<int>& nums, int k) {
        if (nums.size() <= 1) {
            return (int)nums.size();
        }
        std::sort(nums.begin(), nums.end());

        std::queue<int> q;
        std::map<int, int> m;
        int res = 0;

        //initialize map
        int min = nums[0]-1;
        for (int i = 0; i < nums.size(); i++) {
            nums[i] -= min;
            if (m.find(nums[i]) != m.end()) {
                m[nums[i]] += 1;
            } else {
                m[nums[i]] = 1;
            }
        }

        //for (auto i = m.begin(); i != m.end(); i++) {
          //  printf("%d: %d\n", i -> first, i -> second);
        //}

        int temp_count = 0;
        long long q_sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i < nums.size() - 1 && nums[i] == nums[i+1]) {
                continue;
            }
            q.push(nums[i]);
            q_sum += nums[i]*m[nums[i]];
            temp_count += m[nums[i]];
            printf("nums[i]: %d\n", nums[i]);
            printf("queue front: %d\n", q.front());
            printf("temp_count: %d\n", temp_count);

            int insuff = temp_count*nums[i] - q_sum - k; //当前需要的补足数和实际补足数之差
            printf("insuff: %d\n", insuff);
            if (insuff <= 0 && temp_count > res) {
                    res = temp_count;
                    printf("\n");
                    continue;
            }
            while (insuff > 0) {
                int f = q.front();
                if (insuff - (nums[i]-f)*m[f] > 0) {
                    q_sum -= f*m[f];
                    temp_count -= m[f];
                    insuff = temp_count*nums[i] - q_sum - k;
                    q.pop();
                    continue;
                }
                else {
                    int cost = insuff/(nums[i] - f);
                    if (nums[i] == 90) {
                        printf("f: %d\n", f);
                        printf("cost: %d\n", cost);
                        printf("insuff % (nums[i]-f): %d\n", insuff % (nums[i]-f));
                    }
                    if (insuff % (nums[i] - f) != 0) {
                        cost++;
                    }

                    m[f] -= cost;
                    q_sum -= f*cost;
                    temp_count -= cost;
                    insuff -= cost*(nums[i]-f);
                }
            }
            if (temp_count > res) {
                res = temp_count;
            }
            printf("queue front: %d\n", q.front());
            printf("temp_count: %d\n\n", temp_count);
        }
        return res;
    }
};

int main() {
    vector<int> nums = {9942,9983,9986,9997,9925,9976,9983,9942,9914,9980,9952,9989,9912,9978,9910,9927,9934,9907,9934,9912,9910,9920,9999,9912,9965,9927,9932,9987,9995,9919,9966,9991,9964,9961,9990,9913,9923,9937,9919,9965,9967,9981,9914,9973,9928,9940,9901,9906,9994,9905,9936,9992,9901,9903,9985,9979,9915,9984,9992,9989,9948,9971,9949,9969,9982,9978,9981,9907,9976,9936,9979,9975,9962,9915,9956,9963,9959,9950,9973,9914,9936,9967,9914,9956,9903,9996,9975,9925,9938,9906,9915,9902,9907,9902,9994,9917,9935,9927,9929,9973,9976,9961,9929,9915,9901,9927,9974,9916,9988,9902,9908,9999,9975,9908,9919,9954,9947,9952,9913,9905,9958,9978,9971,9983,9937,9998,9933,9906,9936,9938,9985,9918,9987,9939,9971,9964,9941,9935,9928,9967,9915,9988,9963,9988,9920,9958,9940,9967,9935,9988,9994,9972,9974,9977,9995,9985,9956,9975,9935,9925,9904,9965,9999,9973,9961,9985,9962,9954,9998,9972,9990,9958,9909,9921,9902,9989,9947,9953,9976,9978,9932,9929,9955,9939,9961,9919,9948,9928,9982,9944,9983,9935,9975,9986,9907,9952,9979,9939,9950,9906,9929,9977,9940,9961,9990,9955,9935,9915,9967,9900,9943,9900,9970,9979,9919,9946,9936,9937,9908,9951,9969,9978,9947,9936,9916,9920,9900,9984,9940,9950,9900,9961,9989,9905,9914,9907,9918,9907,9999,9986,9984};
    Solution s;
    int res = s.maxFrequency3(nums, 9722);
    printf("res: %d\n", res);
}
