/**********************************************
  > File Name		: peopleAwareOfSecret.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed Aug  3 16:23:38 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <queue>
using namespace std;

int release[1000], forgets[1000], speaker[1000];
int aware[1000];
class Solution {
private:
    static const int mod = 1e9 + 7;
public:
    int peopleAwareOfSecret(int n, const int delay, const int forget) {
        if (n <= delay) return 1;

        memset(release, 0, 1000*sizeof(int));
        memset(forgets, 0, 1000*sizeof(int));
        memset(speaker, 0, 1000*sizeof(int));
        memset(aware, 0, 1000*sizeof(int));

        aware[0] = 1;
        release[delay] = 1;
        forgets[forget] = 1;
        speaker[delay] = 1;
        for (int i = 1; i < n; i++) {
            int new_speaker = ((speaker[i-1] + release[i]) % mod - forgets[i] + mod) % mod;
            int total = ((new_speaker + aware[i-1]) % mod - forgets[i] + mod) % mod;

            if (i + forget < n)
                forgets[i + forget] = new_speaker;
            if (i + delay < n)
                release[i + delay] = new_speaker;
            
            aware[i] = total;
            speaker[i] = new_speaker;
            printf("i = %d, aware = %d, speaker = %d, release = %d, forget = %d\n", i, aware[i], speaker[i], release[i], forgets[i]);
        }
        return aware[n-1];
    }

/*    int peopleAwareOfSecret_(int n, int delay, int forget) {*/
        /*struct Group {*/
            /*int aware_day;*/
            /*int size;*/
            /*Group(int day, int size): aware_day(day), size(size) {}*/
        /*};*/

        /*queue<Group> due, wait;*/
        /*int day = 0;*/
        /*int res = 1, size = 0;*/

        /*wait.push(Group(day, 1));*/

        /*while (day < n) {*/
            /*printf("\n day %d\n", day);*/

            /*while (!due.empty() && due.front().aware_day + forget <= day) {*/
                /*size -= due.front().size;*/
                /*res -= due.front().size;*/
                /*printf("due forget %llu\n", due.front().size);*/
                /*due.pop();*/
            /*}*/

            /*while (!wait.empty() && wait.front().aware_day + delay <= day) {*/
                /*due.push(wait.front());*/
                /*size += wait.front().size;*/
                /*//size %= mod;*/
                /*printf("due add %llu\n", wait.front().size);*/
                /*wait.pop();*/
            /*}*/

            /*if (size > 0)*/
                /*wait.push(Group(day, size)), printf("wait add %llu\n", size);*/
            /*day++;*/
            /*res += size;*/
            /*res %= mod;*/
            /*printf("total size: %llu\n", res);*/
        /*}*/
        /*return res;*/
    /*}*/
};

int main(int argc, char** argv) {
    Solution().peopleAwareOfSecret(atoi(argv[1]), 2, 4);
}
