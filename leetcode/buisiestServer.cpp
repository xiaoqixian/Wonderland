/**********************************************
  > File Name		: buisiestServer.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Wed 05 Jan 2022 09:40:27 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <queue>
#include "printv.h"
#include <cassert>
using namespace std;

/*template <typename T>*/
/*class priority_queue {*/
/*private:*/
    /*vector<T> inner;*/
    /*int alloc;*/

/*public:*/
    /*void swim(int k) {*/
        /*while (k > 1 && this->comp(k, k/2)) {*/
            /*this->exch(k, k/2);*/
            /*k /= 2;*/
        /*}*/
    /*}*/

    /*int sink(int k) {*/
        /*int j;*/

        /*while (k<<1 <= this->alloc) {*/
            /*j = k<<1;*/
            /*if (j < this->alloc && this->comp(j+1, j))*/
                /*j++;*/
            /*if (!this->comp(j, k))*/
                /*break;*/
            /*this->exch(j, k);*/
            /*k = j;*/
        /*}*/
        /*return k;*/
    /*}*/

    /*priority_queue() {*/
        /*this->inner = vector<pair<int, int>>();*/
        /*this->alloc = 0;*/
    /*}*/

    /*priority_queue(int k) {*/
        /*this->inner = vector<pair<int, int>>(k+1, make_pair(0, 0));*/
        /*this->alloc = k;*/
        /*for (int i = 1; i <= k; i++) {*/
            /*this->inner[i].second = i-1;*/
        /*}*/
    /*}*/

    /*pair<int, int> operator[](int index) {*/
        /*if (index >= this->alloc) {*/
            /*printf("index %d exceeds size %d\n", index, this->alloc);*/
            /*return make_pair(-1, -1);*/
        /*}*/

        /*return this->inner[index];*/
    /*}*/

    /*pair<int, int> pop() {*/
        /*if (this->inner.size() == 0) {*/
            /*return make_pair(-1, -1);*/
        /*}*/

        /*pair<int, int> res = this->inner[1];*/
        /*this->exch(1, this->inner.size());*/
        /*this->inner.pop_back();*/
        /*this->sink(1);*/
        /*return res;*/
    /*}*/

    /*void push(int i, int k) {*/
        /*pair<int, int> item = make_pair(i, k);*/
        /*if (this->inner.empty()) {*/
            /*this->inner.push_back(item);*/
        /*}*/

        /*this->inner.push_back(item);*/
        /*this->alloc++;*/
        /*this->swim(this->alloc);*/
    /*}*/

    /*void reassign(int k) {*/
        /*if (k >= this->alloc) {*/
            /*printf("index %d exceedsd size %d\n", k, this->alloc);*/
            /*return;*/
        /*}*/

    /*}*/

    /*void exch(int i, int k) {*/
        /*pair<int, int> temp = this->inner[i];*/
        /*this->inner[i] = this->inner[k];*/
        /*this->inner[k] = temp;*/
    /*}*/

    /*bool comp(int i, int k);*/
/*};*/

/*template <>*/
/*bool priority_queue<int>::comp(int i, int k) {*/
    /*return this->inner[i] < this->inner[k];*/
/*}*/

/*template <>*/
/*bool priority_queue<pair<int, int>>::comp(int i, int k) {*/
    /*return this->inner[i].first < this->inner[k].first;*/
/*}*/

class Compare1 {
public:
    bool operator()(pair<int, int> lhs, pair<int, int> rhs) {
        return lhs.first > rhs.first;
    }
};

class Compare2 {
public:
    bool operator()(pair<int, int> lhs, pair<int, int> rhs) {
        return lhs.second > rhs.second;
    }
};

struct Node {
public:
    int val;
    Node* next;
    Node* prev;
    Node(int val): val(val), next(nullptr), prev(nullptr) {}

    void link(Node* node) {
        node->next = this->next;
        node->prev = this;
        this->next = node;
        if (node->next != nullptr) {
            node->next->prev = node;
        }
    }

    void link_prev(Node* node) {
        node->prev = this->prev;
        node->next = this;
        this->prev = node;
        if (node->prev != nullptr) {
            node->prev->next = node;
        }
    }

    //remove next node and free
    void remove() {
        if (this->next == nullptr)
            return;
        Node* temp = this->next;
        this->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = this;
        }
        delete(temp);
    }
};

class list {
public:
    Node* head;
    Node* end;
    list() {
        this->head = nullptr;
        this->end = nullptr;
    }

    void push_back(int val) {
        if (this->head == nullptr) {
            this->head = new Node(val);
            this->end = this->head;
            return;
        }
        this->end->next = new Node(val);
        this->end->next->prev = this->end;
        this->end = this->end->next;
    }

    bool empty() {
        return this->head == nullptr;
    }

    void show() {
        if (this->head == nullptr) {
            printf("empty list\n");
            return;
        }
        printf("%d", this->head->val);
        Node* temp = this->head->next;
        while (temp != nullptr) {
            printf("->%d", temp->val);
            temp = temp->next;
        }
        printf("\n");
    }
};

template <typename T>
void show_pq(const priority_queue<pair<int, int>, vector<pair<int, int>>, T>& pq) {
    if (pq.empty()) {
        printf("empty priority_queue\n");
        return;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, T> cp = pq;
    pair<int, int> entry;
    if (!cp.empty()) {
        entry = cp.top();
        printf("(%d, %d)", entry.first, entry.second);
        cp.pop();
    }

    while (!cp.empty()) {
        entry = cp.top();
        printf("->(%d, %d)", entry.first, entry.second);
        cp.pop();
    }
    printf("\n");
}

class Solution {
public:
    vector<int> busiestServers1(int k, vector<int>& arrival, vector<int>& load) {
        vector<pair<int, int>> server_loads = vector<pair<int, int>>(k, make_pair(0, 0));
        vector<int> server_finishes = vector<int>(k, 0);
        int n = arrival.size();

        for (int i = 0; i < n; i++) {
            int index = i % k, t = index, time = arrival[i];
            int tsp = server_loads[index].first, server_load = server_loads[index].second;
            while (tsp + server_load > time) {
                ++t %= k;
                if (t == index)
                    break;
                tsp = server_loads[t].first, server_load = server_loads[t].second;
            }

            if (t == index) //can't find an avaliable server
                continue;

            server_loads[t] = make_pair(time, load[i]);
            server_finishes[t]++;
        }

        int max = 0;
        vector<int> res;
        for (int i = 0; i < k; i++) {
            if (server_finishes[i] > max) {
                res.clear();
                res.push_back(i);
                max = server_finishes[i];
            } else if (server_finishes[i] == max) {
                res.push_back(i);
            }
        }
        return res;
    }

    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& loads) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare1> busy;
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare2> holds;
        list avaliable;
        bool flag = true;
        vector<int> server_loads(k, 0);

        for (int i = 0; i < k; i++) {
            //if (flag && k > 50 && i > k/2) {
                //half = avaliable.crbegin();
                //flag = false;
            //}
            avaliable.push_back(i);
        }

        avaliable.show();

        int size = arrival.size();
        for (int i = 0; i < size; i++) {
            int time = arrival[i], load = loads[i], index = i % k;
            printf("\nprocess time %d, load %d, i %d, index %d\n", time, load, i, index);

            printf("busy: "); show_pq(busy); printf("holds: "); show_pq(holds);
            bool added = false;
            if (!busy.empty()) {
                pair<int, int> front = busy.top();
                while (!busy.empty() && time >= front.first) {
                    if (front.second == index) {
                        server_loads[index]++;
                        printf("find from holds\n");
        printf("%d recv at %d, server_loads: ", __LINE__, index); printv(server_loads);
                        added = true;
                        busy.pop();
                        busy.push(make_pair(time + load, index));
                        break;
                    }

                    holds.push(front);
                    busy.pop();
                    front = busy.top();
                }
            }

            if (added)
                continue;
            printf("busy: "); show_pq(busy); printf("holds: "); show_pq(holds);

            printf("1. avaliable list: "); avaliable.show();
            pair<int, int> front;
            Node* temp = avaliable.head;
            bool flag = true;
            if (!holds.empty()) {
                if (temp == nullptr) { //avaliable is empty
                    while (!holds.empty()) {
                        front = holds.top();
                        if (front.second >= index) {
                            server_loads[front.second]++;
        printf("%d recv at %d, server_loads: ", __LINE__, front.second); printv(server_loads);
                            added = true;
                            busy.push(make_pair(time + load, front.second));
                            holds.pop();
                            break;
                        }
                        avaliable.push_back(front.second);
                        holds.pop();
                    }
                } else {
                    front = holds.top();
                    while (!holds.empty() && temp->val > front.second) {
                        if (front.second >= index) {
                            server_loads[front.second]++;
        printf("%d recv at %d, server_loads: ", __LINE__, front.second); printv(server_loads);
                            added = true;
                            busy.push(make_pair(time + load, front.second));
                            holds.pop();
                            break;
                        }

                        Node* new_node = new Node(front.second);
                        if (flag) {
                            avaliable.head = new_node;
                            temp->prev = new_node;
                            new_node->next = temp;
                            flag = false;
                        } else {
                            assert(temp->prev->val < front.second);
                            temp->prev->next = new_node;
                            new_node->next = temp;
                            temp->prev = new_node;
                        }
                        
                        holds.pop();
                        if (holds.empty()) {
                            front.second = -1;
                            break;
                        }
                        front = holds.top();
                    }
                }
            }

            if (added)
                continue;

            printf("2. avaliable list: "); avaliable.show();
            int recv_server = -1;
            flag = true;
            while (temp != nullptr) {
                if (flag && index < temp->val && temp->prev != nullptr && index < temp->prev->val) {
                    printf("%d can't be after %d cause before %d is %d\n", index, temp->val, temp->val, temp->prev->val);
                    break;
                }
                flag = false;
                printf("temp = %d\n", temp->val);

                //if front.second is between temp->val and temp->next->val, insert it.
                if (temp->val < front.second && (temp->next == nullptr ? true : temp->next->val > front.second)) {
                    //printf("add %d to list\n", front.second);
                    Node* new_node = new Node(front.second);
                    new_node->next = temp->next;
                    temp->next = new_node;
                    new_node->prev = temp;
                    if (new_node->next != nullptr)
                        new_node->next->prev = new_node;

                    holds.pop();
                    if (holds.empty())
                        front.second = -1;
                    else
                        front = holds.top();
                }
                
                if (temp->val >= index) {
                    recv_server = temp->val;

                    if (temp->prev == nullptr) {
                        avaliable.head = temp->next;
                    } else {
                        temp->prev->next = temp->next;
                    }

                    if (temp->next == nullptr) {
                        avaliable.end = temp->prev;
                    } else {
                        temp->next->prev = temp->prev;
                    }

                    delete(temp);
                    break;
                }

                temp = temp->next;
            }
            printf("3. avaliable list: "); avaliable.show();

            if (recv_server == -1) {
                if (avaliable.head == nullptr) {
                    printf("time %d, load %d, i %d, index %d skipped\n", time, load, i, index);
                    continue;
                } else {
                    recv_server = avaliable.head->val;
                    temp = avaliable.head;
                    avaliable.head = avaliable.head->next;
                    if (temp->next != nullptr) {
                        temp->next->prev = nullptr;
                    }
                    delete(temp);
                }
            } 
            
            printf("4. avaliable list: "); avaliable.show();
            server_loads[recv_server]++;
        printf("%d recv at %d, server_loads: ", __LINE__, recv_server); printv(server_loads);
            busy.push(make_pair(time + load, recv_server));
        }

        printf("\nserver_loads: "); printv(server_loads);
        int max = 0;
        vector<int> res;
        for (int i = 0; i < k; i++) {
            if (server_loads[i] > max) {
                res.clear();
                res.push_back(i);
                max = server_loads[i];
            } else if (server_loads[i] == max) {
                res.push_back(i);
            }
        }
        return res;
    }
};

int main() {
    //vector<int> arrival = {1,2,3,4}, load = {1,2,1,2};
    //vector<int> arrival = {1,2,3,4,5}, load = {5,2,3,3,3};
    //vector<int> arrival = {1,3,4,5,6,11,12,13,15,19,20,21,23,25,31,32};
    //vector<int> load = {9,16,14,1,5,15,6,10,1,1,7,5,11,4,4,6};
    //vector<int> arrival = {1,3,6,7,8,9,10,14,16,20,21,24,25,28,29,30,33,34};
    //vector<int> load = {20,27,27,14,14,9,15,8,23,1,34,2,28,25,7,6,24,15};
    //vector<int> arrival = {5,6,12,14,19,21,25,29,46,49,56,57,58,63,71,72,76,77,79,80,85,90,106,108,109,111,112,116,125,135,142,143,159,160,162,164,166,167,172,173,177,179,183,185,193,196,212,213,226,242,244,245,256,258,263,266,272,274,296,298,311,312,318,320};
    //vector<int> load = {10,50,2,29,9,43,2,46,28,46,56,30,37,4,61,11,25,62,50,31,42,50,11,60,54,57,12,62,8,32,61,62,62,44,64,41,36,55,5,46,52,64,1,41,58,50,46,4,21,10,48,38,33,43,55,28,20,32,26,12,28,33,13,32};
    vector<int> arrival = {13,67,68,72,74,82,83,87,108,112,113,121,137,142,154,157,165,182,197,217,221,257,262,269,279,295,297,304,312,318,330,339,347,348,366,373,379,399,401,402,413,434,437,438,445,460,463,492,504,524,542,548,567,570,583,594,595,614,617,643,644,660,690,692,703,722,727,740,748,753,767,775,793,804,808,811,816,825,832,835,838,858,861,867,876,881,893,899,906,934,944,947,948,949,980,982,997,1000,1003,1005,1042,1048,1067,1076,1086,1107,1136,1142,1153,1175,1187,1189,1196,1199,1201,1205,1206,1212,1213,1217,1228,1248,1255,1262,1293,1327,1328,1333,1335,1361,1369,1374,1396,1406,1419,1421,1423,1445,1460,1472,1474,1480,1483,1497,1506,1529,1581,1584,1593,1612,1629,1638,1648,1650,1662,1664,1673,1684,1688,1696,1712,1717,1731,1733,1736,1747,1757,1765,1777,1809,1811,1815,1822,1825,1828,1840,1842,1843,1857,1870,1874,1878,1881,1888,1889,1903,1909,1924,1927,1930,1959,1965,1967,1980,1997,2014,2027,2037,2068,2070,2071,2090,2094,2098,2108,2110,2132,2137,2150,2156,2161,2168,2172,2198,2205,2207,2231,2244,2248,2261,2275,2279,2280,2292,2300,2303,2308,2327,2344,2355,2360,2369,2391,2402,2410,2421,2426,2435,2439,2453,2459,2469,2476,2479,2489,2496,2499,2516,2530,2546,2550,2576,2590,2595,2599,2609,2610,2619,2632,2636,2644,2688,2698,2699,2716,2717,2746,2753,2781,2799,2804,2812,2822,2826,2827,2832,2839,2843,2844,2861,2873,2879,2882,2892,2896,2909,2912,2930,2933,2936,2943,2957,2958,2982,2990,2996,2997,2999,3019,3021,3027,3031,3037,3038,3055,3064,3068,3070,3072,3076,3082,3093,3096,3097,3104,3146,3149,3183,3186,3192,3198,3207,3215,3234,3236,3237,3238,3254,3256,3264,3275,3278,3287,3302,3306,3312,3323,3329,3339,3346,3360,3368,3382,3405,3453,3467,3469,3471,3476,3485,3486,3487,3488,3525,3539,3565,3590,3592,3605,3606,3607,3614,3619,3622,3625,3631,3634,3640,3645,3657,3671,3678,3690,3693,3696,3699,3707,3719,3720,3721,3723,3733,3737,3738,3745,3747,3763,3786,3790,3806,3810,3814,3820,3828,3839,3854,3857,3858,3862,3870,3884,3891,3899,3923,3925,3966,3973,3977,3996,4014,4023,4035,4037,4038,4043,4051,4053,4057,4060,4086,4095,4101,4106,4113,4127,4129,4133,4162,4163,4168,4171,4181,4187,4200,4212,4215,4230,4236,4238,4243,4265,4280,4299,4304,4339,4350,4353,4364,4373,4379,4421,4426,4437,4439,4459,4469,4481,4487,4498,4525,4531,4532,4545,4550,4552,4559,4574,4585,4594,4596,4603,4604,4624,4630,4640,4645,4669,4674,4687,4689,4704,4716,4725,4728,4735,4743,4750,4762,4772,4791,4808,4809,4820,4830,4835,4849,4856,4869,4881,4926,4931,4934,4952,4962,4975,4983,4998,5000,5003,5007,5008,5009,5016,5020,5025,5034,5036,5038,5054,5066,5076,5111,5120,5131,5135,5137,5153,5165,5183,5193,5232,5241,5249,5269,5274,5291,5295,5305,5315,5327,5329,5330,5334,5349,5352,5360,5369,5404,5460,5468,5473,5480,5510,5530,5544,5548,5557,5560,5564,5572,5575,5604,5625,5627,5631,5638,5639,5658,5662,5664,5675,5681,5684,5688,5690,5709,5712,5739,5740,5753,5765,5769,5775,5810,5821,5827,5828,5835,5839,5842,5880,5922,5941,5952,5959,5977,5992,5999,6013,6015,6022,6028,6034,6044,6047,6053,6057,6068,6078,6082,6105,6110,6132,6140,6155,6160,6169,6178,6188,6209,6224,6229,6255,6274,6276,6279,6280,6297,6298,6310,6312,6320,6329,6346,6351,6356,6360,6372,6389,6394,6397,6406,6407,6414,6423,6432,6438,6448,6468,6486,6495,6521,6536,6541,6543,6551,6552,6568,6569,6572,6581,6605,6612,6619,6627,6629,6632,6651,6655,6656,6658,6666,6672,6677,6683,6699,6701,6704,6705,6706,6710,6749,6767,6775,6779,6785,6790,6791,6814,6824,6829,6849,6853,6854,6859,6860,6861,6900,6919,6921,6944,6953,6963,6974,6977,6983,6994,7004,7025,7033,7035,7047,7065,7071,7072,7084,7087,7089,7091,7109,7124,7130,7154,7158,7168,7189,7197,7215,7217,7231,7243,7245,7255,7269,7271,7279,7291,7292,7300,7308,7317,7320,7337,7342,7344,7345,7356,7357,7358,7359,7360,7364,7371,7415,7417,7424,7441,7462,7463,7467,7470,7474,7482,7483,7489,7492,7514,7520,7538,7548,7568,7580,7597,7613,7625,7626,7639,7648,7691,7692,7694,7696,7701,7703,7733,7742,7775,7783,7790,7794,7807,7812,7814,7821,7840,7844,7852,7865,7868,7869,7871,7891,7892,7899,7914,7927,7939,7946,7967,7978,7993,8011,8013,8017,8018,8040,8057,8062,8069,8072,8074,8084,8086,8114,8116,8131,8141,8145,8186,8200,8220,8222,8235,8238,8272,8282,8290,8291,8297,8298,8317,8332,8346,8374,8381,8385,8421,8446,8450,8470,8472,8477,8503,8510,8536,8553,8562,8567,8583,8584,8587,8600,8612,8613,8645,8657,8676,8683,8695,8698,8717,8719,8745,8751,8754,8755,8762,8771,8773,8777,8780,8787,8793,8795,8800,8814,8841,8846,8867,8872,8878,8897,8904,8909,8917,8919,8920,8947,8953,8954,8975,8976,8988,8999,9001,9024,9039,9047,9048,9054,9062,9079,9082,9102,9105,9154,9162,9177,9187,9208,9209,9211,9222,9229,9273,9287,9320,9321,9333,9363,9364,9369,9373,9385,9388,9401,9416,9426,9436,9446,9463,9467,9470,9474,9478,9480,9482,9499,9500,9503,9511,9512,9545,9558,9560,9566,9570};
    vector<int> load = {1002,2649,2307,1134,3592,1204,57,3584,1860,1423,2329,3399,1196,741,2373,44,808,2479,967,1975,1032,639,3694,846,3216,1624,389,3658,3794,1891,1595,206,1604,1703,1741,1487,2537,161,2309,706,3478,1739,3302,994,2760,472,1790,2006,998,3328,560,406,2082,2729,3770,1574,2255,2719,2513,3480,1738,2306,536,314,983,1894,2429,3403,3287,1131,81,217,1389,167,1469,2641,813,2318,1228,211,892,72,2435,3086,368,1688,2649,1922,2663,2148,1328,8,3382,2,960,2917,1313,2092,1632,3077,582,3548,2585,172,310,2010,3532,3426,684,1082,3179,211,2463,808,2357,1817,919,553,1015,3806,3436,1124,3537,985,2767,818,3442,1916,3807,1456,1254,931,1676,1446,305,1759,2793,374,3318,973,88,3508,1219,2894,801,1546,1647,1665,1642,3098,2020,1423,1998,901,2863,2123,2850,2806,3398,1940,3098,1194,2985,705,2061,381,1324,599,726,1776,794,943,3215,637,1805,2264,2042,1995,1539,2896,2201,2816,2450,1582,858,3787,3101,1669,1815,3419,3291,718,2299,1568,2247,2569,2332,845,75,1163,3066,3240,2651,3230,2556,569,2854,718,2603,3187,1542,98,2937,942,2536,3812,222,3551,1887,3686,433,2862,1999,2130,1250,826,2476,3357,3092,991,3751,2168,493,1993,3044,1054,607,2459,2022,2260,3571,1766,950,157,1562,1587,1061,912,1715,885,808,2255,3644,998,2740,2252,1566,818,2072,3685,1715,3457,2041,491,2864,1870,1304,1774,1095,3783,135,3167,70,1090,3344,2524,2654,2144,2510,2776,1913,2331,397,1368,2171,3572,2697,1760,2418,3280,2245,743,1397,3080,1717,2107,2337,2799,2108,3731,2216,2601,3674,2357,3561,3370,3592,3700,156,2463,2944,2521,1423,1257,2416,2265,1568,281,3518,1672,2083,1453,3442,1051,3515,96,216,688,627,1069,3328,1,1470,3121,448,3722,543,908,2677,1502,2500,2295,1387,691,1896,1360,1100,2753,3146,1076,2972,1942,1899,1897,2741,2879,2608,2159,188,2542,2023,1186,1713,3273,1897,2584,3015,3691,2820,2486,2876,2693,2519,798,26,2139,1267,1880,2186,3772,330,808,95,882,2314,1436,3340,3255,3,321,1916,1451,859,272,188,3526,1820,848,3038,3710,3751,736,2323,157,3553,2985,2912,3259,3804,2383,2913,3615,1040,3228,2913,1674,3120,249,3346,3646,1788,3424,3729,1256,1755,1175,1390,551,3520,1550,1549,1347,18,412,3085,950,3281,936,3332,1986,2117,1554,3529,587,1446,2791,451,635,2512,2585,3676,1987,1440,2621,447,317,750,3073,1856,3628,2300,1345,2178,2321,3003,1852,2284,1149,332,3043,17,1065,128,614,795,2238,1051,1231,1841,2558,2991,2879,188,2949,1994,1178,40,2239,2218,1474,153,1673,106,1696,1448,721,3773,3501,3549,2019,1553,1827,1772,1395,3506,463,2350,1650,2610,87,1404,3717,840,2933,1687,3495,3025,909,705,95,1546,2411,1917,2506,2287,2330,2771,1860,260,1292,2475,2628,2511,869,221,819,142,2412,2434,816,2244,2914,1961,857,1841,1669,1025,101,2963,3815,490,3797,1839,1481,264,2994,2002,2638,2461,1534,2579,2989,603,1562,775,200,3518,3649,3791,1886,1485,1592,266,259,3191,3494,1213,2534,2304,1105,626,176,1685,485,2408,519,2516,827,1917,3474,729,61,2049,3385,3457,77,2101,2075,350,1082,2336,236,576,2976,347,786,3712,887,2314,1717,3209,637,3326,991,3253,314,2907,2920,1361,3487,2283,486,2266,210,3319,2542,2115,3176,3229,1280,3611,336,3828,647,845,2276,3004,292,2586,985,1807,1250,1204,1554,307,1328,3655,2204,659,2873,1537,1811,1703,155,107,2307,1260,3712,2966,1501,561,3045,409,1185,3823,989,1581,1424,432,1464,656,2022,3595,1932,3686,2742,1777,1811,2186,575,2278,3587,460,774,1663,1705,2549,3017,3304,2576,3439,1928,2187,482,3180,3294,1511,292,2401,345,1857,1750,2058,441,3271,1553,915,2052,3403,1510,3451,3073,3530,2865,6,323,1809,490,1445,957,1421,1425,1452,1565,3747,558,3700,3822,1537,3584,1578,955,652,2408,953,2699,3038,3715,717,623,649,3398,1233,85,2588,2235,2283,1492,3504,396,2677,2876,296,189,1021,527,307,3282,3124,2217,1234,2078,3013,2058,671,130,1123,1064,596,3762,3107,1597,1511,25,1584,50,190,1133,2589,2677,2702,170,1059,563,1785,3435,519,1279,506,744,878,652,3678,3051,3078,377,1415,777,872,814,665,2821,114,547,921,727,2107,1908,3418,1943,3818,3716,1809,1324,325,948,2950,3397,2965,2261,2246,11,2852,2104,1288,71,37,487,249,94,1383,810,2821,2222,2969,163,2860,374,1824,3653,1655,569,3088,1525,3497,2362,3114,1237,677,1710,158,667,2599,1270,1504,791,219,2673,3322,354,869,511,54,1747,1859,2473,1864,7,842,1153,3089,705,1207,2456,256,2394,2990,3097,3446,2461,1362,910,3087,3664,619,3236,2841,510,809,3479,1718,3583,3262,922,3539,1141,3039,1100,241,676,1061,2341,1972,1063,2186,401,2732,2001,1730,1402,1051,2837,3134,3729,1045,1891,2271,3563,1958,1095,787,3292,3108,441,2198,1517,1002,1706,425,2911,3436,1868,2866,1134,2124,3283,1216,14,1694,2810,3088,3743,1681,1761,3278,1198,458,2815,1659,3683,257,631,1687,621,1957,3247,2030};
    Solution s;
    vector<int> res = s.busiestServers(82, arrival, load);
    printv(res);
}
