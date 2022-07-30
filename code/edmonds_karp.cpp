/**********************************************
  > File Name		: edmonds_karp.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sat 01 Jan 2022 09:02:59 PM CST
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

/**
 * Edmonds-Karp algorithm finds the maximum flow in a network graph.
 */

#include <vector>
#include <stdio.h>
#include <cstring>
#include <queue>

using namespace std;

#define maxn 250
#define INF 0x3f3f3f3f

struct Edge {
  int from, to, cap, flow;
  Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}

  void say() {
      printf("%c -> %c, cap: %d, flow: %d\n", (char)from, (char)to, cap, flow);
  }
};

struct EK {
    int v, e;             // v: number of vertex, e: number of edges.
    vector<Edge> edges;   
    vector<int> G[maxn];  // G: G[i] contains all indexes of edges start with i
    int a[maxn], p[maxn];

    void init(int n) {
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void addEdge(char from, char to, int cap) {
        edges.push_back(Edge((int)from, (int)to, cap, 0));
        edges.push_back(Edge((int)to, (int)from, 0, 0));
        int m = edges.size();
        G[(int)from].push_back(m - 2);
        G[(int)to].push_back(m - 1);
    }

    int maxFlow(int s, int t) {
        int flow = 0;

        while (1) {
            memset(a, 0, sizeof(a));
            queue<int> q;
            q.push(s);
            a[s] = INF;

            while (!q.empty()) {
                int x = q.front();
                q.pop();

                for (int index: G[x]) {
                    Edge& edge = this->edges[index];
                    
                    if (!this->a[edge.to] && edge.cap > edge.flow) {
                        this->p[edge.to] = index;
                        this->a[edge.to] = min(this->a[x], edge.cap - edge.flow);
                        q.push(edge.to);
                    }
                }

                if (this->a[t]) {
                    break;
                }
            }

            if (!this->a[t]) {
                break;
            }

            for (int u = t; u != s; u = edges[p[u]].from) {
                edges[p[u]].flow += this->a[t];
                edges[p[u] ^ 1].flow -= this->a[t];
                edges[p[u]].say();
                edges[p[u] ^ 1].say();
            }
            printf("\n");
            flow += this->a[t];
        }
        return flow;
    }
};

int main() {
    EK ek;
    //ek.addEdge('S', 'A', 16);
    //ek.addEdge('A', 'B', 12);
    //ek.addEdge('S', 'C', 13);
    //ek.addEdge('C', 'A', 4);
    //ek.addEdge('B', 'C', 9);
    //ek.addEdge('C', 'D', 14);
    //ek.addEdge('D', 'B', 7);
    //ek.addEdge('D', 'T', 4);
    //ek.addEdge('B', 'T', 20);
    ek.addEdge('A', 'B', 3);
    ek.addEdge('A', 'D', 2);
    ek.addEdge('D', 'E', 2);
    ek.addEdge('B', 'E', 3);
    ek.addEdge('B', 'C', 2);
    ek.addEdge('E', 'F', 3);
    ek.addEdge('C', 'F', 2);
    
    printf("%d\n", ek.maxFlow((int)'A', (int)'F'));
}
