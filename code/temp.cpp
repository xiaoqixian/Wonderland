/**********************************************
  > File Name		: temp.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Sun 02 Jan 2022 04:50:40 PM CST
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
#include <unistd.h>

using namespace std;

#define N 250
#define M 250
#define INF 0x3f3f3f3f

struct qxx {
  int nex, t, v, c;
};
qxx e[M];
int h[N], cnt = 1;
void add_path(int f, int t, int v, int c) {
  e[++cnt] = (qxx){h[f], t, v, c}, h[f] = cnt;
}
void add_flow(int f, int t, int v, int c) {
  add_path(f, t, v, c);
  add_path(t, f, 0, -c);
}
int dis[N], pre[N], incf[N];
bool vis[N];
int s, t;
bool spfa() {
  memset(dis, 0x3f, sizeof(dis));
  queue<int> q;
  q.push(s), dis[s] = 0, incf[s] = INF, incf[t] = 0;
  while (q.size()) {
    int u = q.front();
    q.pop();
    vis[u] = 0;
    for (int i = h[u]; i; i = e[i].nex) {
      const int &v = e[i].t, &w = e[i].v, &c = e[i].c;
      if (!w || dis[v] <= dis[u] + c) continue;
      dis[v] = dis[u] + c, incf[v] = min(w, incf[u]), pre[v] = i;
      if (!vis[v]) q.push(v), vis[v] = 1;
    }
  }
  return incf[t];
}
int maxflow = 0, mincost = 0;
void update() {
  maxflow += incf[t];
  for (int u = t; u != s; u = e[pre[u] ^ 1].t) {
    e[pre[u]].v -= incf[t], e[pre[u] ^ 1].v += incf[t];
    mincost += incf[t] * e[pre[u]].c;
  }
}

int main() {
    add_path((int)'S', (int)'A', 8, 2);
    add_path((int)'S', (int)'B', 7, 8);
    add_path((int)'A', (int)'B', 5, 5);
    add_path((int)'A', (int)'C', 9, 2);
    add_path((int)'C', (int)'B', 2, 1);
    add_path((int)'B', (int)'D', 9, 3);
    add_path((int)'D', (int)'C', 6, 4);
    add_path((int)'D', (int)'T', 10, 7);
    add_path((int)'C', (int)'T', 5, 6);
    while (spfa()) {
        update();
    }
    printf("<%d, %d>\n", maxflow, mincost);
}
