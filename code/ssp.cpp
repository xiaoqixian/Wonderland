/**********************************************
  > File Name		: ssp.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 02 Jan 2022 03:52:24 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/**
 * SSP: max flow based on Edmonds-Karp algorithm, shortest path based on Bellman-Ford.
 */
#include <vector>
#include <stdio.h>
#include <cstring>
#include <queue>
#include <stack>
#include <unistd.h>

using namespace std;

#define maxn 250
#define INF 0x3f3f3f3f

struct Edge {
  int from, to, cap, flow, cost;
  Edge(int u, int v, int cap, int f, int cost) : from(u), to(v), cap(cap), flow(f), cost(cost) {}

  void say() {
      printf("%c -> %c, cap: %d, flow: %d\n", (char)from, (char)to, cap, flow);
  }
};

class SSP {
private:
    vector<Edge> edges;
    vector<int> edge_indice[maxn];
    int dis[maxn], pre[maxn], increase_flow[maxn];
    bool visited[maxn];
    int max_flow, min_cost;

public:
    void addEdge(char f, char t, int cap, int cost) {
        int from = (int)f, to = (int)t;
        this->edges.push_back(Edge(from, to, cap, 0, cost));
        this->edges.push_back(Edge(to, from, 0, 0, -cost));
        int size = edges.size();
        this->edge_indice[from].push_back(size - 2);
        this->edge_indice[to].push_back(size - 1);
    }

    pair<int, int> maxFlowMinCost(char start, char terminate) {
        this->max_flow = 0;
        this->min_cost = 0;
        int s = (int)start, t = (int)terminate;
        
        while (this->spfa(s, t))
            this->update(s, t);
        
        return make_pair(this->max_flow, this->min_cost);
    }

    int spfa(int s, int t) {
        memset(this->dis, INF, sizeof(this->dis));
        queue<int> q;
        q.push(s), this->dis[s] = 0; 
        this->increase_flow[s] = INF, this->increase_flow[t] = 0;

        while (!q.empty()) {
            int x = q.front();
            q.pop();
            this->visited[x] = false;
            
            for (int index: this->edge_indice[x]) {
                Edge& edge = this->edges[index];
                if (edge.flow >= edge.cap || this->dis[edge.to] <= this->dis[x] + edge.cost)//if no capability on this path or shorter path for this vertex, continue.
                    continue;
                this->dis[edge.to] = this->dis[x] + edge.cost;
                this->increase_flow[edge.to] = min(this->increase_flow[x], edge.cap - edge.flow);
                printf("this->increase_flow[%c] = %d\n", edge.to, this->increase_flow[edge.to]);
                this->pre[edge.to] = index;

                if (!this->visited[edge.to]) {
                    this->visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        printf("increase_flow[t] = %d\n", this->increase_flow[t]);
        return this->increase_flow[t];
    }

    void update(int s, int t) {
        this->max_flow += this->increase_flow[t];
        for (int u = t; u != s; u = this->edges[this->pre[u] ^ 1].to) {
            this->edges[this->pre[u]].flow += this->increase_flow[t];
            this->edges[this->pre[u] ^ 1].flow -= this->increase_flow[t];
            this->edges[this->pre[u]].say();
            this->edges[this->pre[u] ^ 1].say();
            this->min_cost += this->edges[this->pre[u]].cost * this->increase_flow[t];
        }
    }
};

int main() {
    SSP ssp;
    ssp.addEdge('S', 'A', 8, 2);
    ssp.addEdge('S', 'B', 7, 8);
    ssp.addEdge('A', 'B', 5, 5);
    ssp.addEdge('A', 'C', 9, 2);
    ssp.addEdge('C', 'B', 2, 1);
    ssp.addEdge('B', 'D', 9, 3);
    ssp.addEdge('D', 'C', 6, 4);
    ssp.addEdge('D', 'T', 10, 7);
    ssp.addEdge('C', 'T', 5, 6);

    auto res = ssp.maxFlowMinCost('S', 'T');
    printf("<%d, %d>\n", res.first, res.second);
}
