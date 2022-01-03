/**********************************************
  > File Name		: maximumRequests.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 01 Jan 2022 06:30:03 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <vector>
#include <stdio.h>
#include <cstring>
#include <queue>
#include <stack>
#include <unistd.h>

using namespace std;

struct Edge {
  int from, to, cap, flow, cost;
  Edge(int u, int v, int cap, int cost) : from(u), to(v), cap(cap), cost(cost) {}

  void say() {
      printf("%c -> %c, cap: %d, cost: %d\n", (char)from, (char)to, cap, cost);
  }
};

#define maxn 22
#define INF 0x3f3f3f3f
class Solution {
private:
    vector<Edge> edges;
    vector<int> edge_indice[maxn];
    int dis[maxn], pre[maxn], increase_flow[maxn];
    bool visited[maxn];
    int max_flow, min_cost;

    void addEdge(int f, int t, int cap, int cost) {
        this->edges.push_back(Edge(f, t, cap, cost));
        this->edges.push_back(Edge(t, f, 0, -cost));
        int size = this->edges.size();
        this->edge_indice[f].push_back(size - 2);
        this->edge_indice[t].push_back(size - 1);
    }

    int spfa(int s, int t) {
        memset(this->dis, INF, sizeof(this->dis));
        this->dis[s] = 0;
        this->increase_flow[s] = INF, this->increase_flow[t] = 0;

        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            this->visited[v] = false;
            
            for (int index: this->edge_indice[v]) {
                Edge& v_edge = this->edges[index];//edge starts with v
                
                if (!v_edge.cap || this->dis[v_edge.to] <= this->dis[v] + v_edge.cost) {
                    continue;
                }

                this->increase_flow[v_edge.to] = min(this->increase_flow[v], v_edge.cap);
                this->dis[v_edge.to] = this->dis[v] + v_edge.cost;
                this->pre[v_edge.to] = index;
                
                if (!this->visited[v_edge.to]) {
                    this->visited[v_edge.to] = true;
                    q.push(v_edge.to);
                }
            }
        }
        return this->increase_flow[t];
    }

    void update(int s, int t) {
        //printf("increase_flow: %d\n", this->increase_flow[t]);
        this->max_flow += this->increase_flow[t];
        
        for (int u = t; u != s; u = this->edges[this->pre[u] ^ 1].to) {
            this->min_cost += this->increase_flow[t] * this->edges[this->pre[u]].cost;
            this->edges[this->pre[u]].cap -= this->increase_flow[t];
            this->edges[this->pre[u] ^ 1].cap += this->increase_flow[t];
        }

    }

public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int degrees[maxn] = {0};
        int movement[maxn][maxn] = {{0}};
        int s = n+1, t = n+2;
        this->max_flow = 0, this->min_cost = 0;

        for (vector<int>& req: requests) {
            movement[req[0]][req[1]]++;
            degrees[req[0]]++;
            degrees[req[1]]--;
        }

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (i != k && movement[i][k]) {
                    this->addEdge(i, k, movement[i][k], 1);
                }
            }
            if (degrees[i] > 0) {
                this->addEdge(s, i, degrees[i], 0);
            } else if (degrees[i] < 0) {
                this->addEdge(i, t, -degrees[i], 0);
            }
        }

        //for (int i = 0; i < n; i++) {
            //if (degrees[i] > 0) {
                //this->addEdge(s, i, degrees[i], 0);
            //} else if (degrees[i] < 0) {
                //this->addEdge(i, t, -degrees[i], 0);
            //}
        //}

        while (this->spfa(s, t)) {
            this->update(s, t);
        }

        return requests.size() - this->min_cost;
    }
};

int main() {
    Solution s;
    //vector<vector<int>> requests = {{0,1},{1,0},{0,1},{1,2},{2,0},{3,4}};
    //vector<vector<int>> requests = {{0, 0}, {1, 2}, {2, 1}};
    //vector<vector<int>> requests = {{1,2},{1,2},{2,2},{0,2},{2,1},{1,1},{1,2}};
    vector<vector<int>> requests = {{0,1},{1,0},{0,1},{1,2},{2,0},{3,4}};
    printf("%d\n", s.maximumRequests(5, requests));
}
