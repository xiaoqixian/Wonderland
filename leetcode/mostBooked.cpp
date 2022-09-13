/**********************************************
  > File Name		: mostBooked.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun Sep  4 11:49:20 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
private:
    struct Room {
        long long start, end;
        int number;
    };
public:
    int mostBooked(const int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end(), [&](const vector<int>& v1, const vector<int>& v2) {return v1[0] >= v2[0];});

        auto cmp = [](const Room& v1, const Room& v2) {
            if (v1.end == v2.end) {
                return v1.number > v2.number;
            } else return v1.end > v2.end;
        };
        typedef priority_queue<Room, vector<Room>, decltype(cmp)> pq_type;

        pq_type pq(cmp);

        for (int i = 0; i < n; i++) {
            pq.push(Room {0, 0, i});
        }

        vector<int> use_times(n, 0);
        long long clock = 0;

        while (!meetings.empty()) {
            const vector<int> mt = meetings.back();
            meetings.pop_back();

            if (clock < mt[0]) {
                clock = mt[0];
            }

            vector<Room> buffer;
            int index = -1;

            while (!pq.empty()) {
                const auto& r = pq.top();
                if (r.end <= clock) {
                    buffer.emplace_back(pq.top());
                    if (index == -1 || r.number < buffer[index].number) {
                        index = buffer.size()-1;
                    }
                    pq.pop();
                } else break;
            }

            for (int i = 0; i < buffer.size(); i++) {
                if (i == index) {
                    continue;
                }
                pq.push(std::move(buffer.at(i)));
            }

            Room room;
            if (index == -1) {
                room = pq.top();
                pq.pop();
            } else {
                room = buffer[index];
            }


            if (clock < room.end) {
                clock = room.end;
            }

            room.start = clock;
            room.end = clock + (mt[1] - mt[0]);
            use_times[room.number]++;
            pq.push(std::move(room));
        }

        int res = -1, max_times = 0;
        for (int i = 0; i < n; i++) {
            if (use_times[i] > max_times) {
                max_times = use_times[i];
                res = i;
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> vv({{1,20},{2,10},{3,5},{4,9},{6,8}});
    printf("%d\n", Solution().mostBooked(3, vv));
}
