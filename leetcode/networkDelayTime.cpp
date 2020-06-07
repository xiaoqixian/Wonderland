/*
 Leetcode: 743.网络延迟时间
 这题本质上是求节点K到各点的最短距离，需要运用到迪杰斯特拉算法 
 由于所有节点的标记为1到N，所以为了减少减法运算，所有数组均创建为N+1的大小，第0位不使用 
 */ 
 
#include <vector>
#include <string.h>
#include <limits.h> 
using namespace std;
 
class Solution {
public:
	int networkDelayTime(vector<vector<int> >& times, int K, int N) { //times结构[u,v,w]，u传递到v，用的时间为w 
		//创建一个邻接矩阵
		int graph[N+1][N+1], size = times.size(), i, j;
		memset(graph, -1, sizeof(graph));
		for (i = 0; i < size; i++) {
			graph[times[i][0]][times[i][1]] = times[i][2];
		}
		//创建一个数组distance表示其他节点到节点K的最短距离
		int distance[N+1];
		//初始化K节点到其可到达节点距离
		for (i = 1; i <= N; i++) {
			distance[i] = graph[K][i];
		}
		distance[K] = 0;
		//创建一个数组visited表示节点是否被访问过
		bool visited[N+1];
		memset(visited, false, sizeof(visited));
		visited[K] = true;
		
		/*接着遍历除节点K之外的N-1各节点 
		  在每次遍历中都要找到当前未访问的离节点K最近的节点。再去比较最近的节点到某节点与K节点直接到达的距离大小并进行更新。
		  如果将K所有可到达的节点都遍历后还有没有访问的节点，则说明该节点信号无嘎传达。 
		 */
		int minDis, minIndex;
		//i用于遍历N-1次，无实际意义 
		for (i = 1; i < N; i++) {
			minDis = INT_MAX;
			minIndex = 1;
			//找到所有可到达节点中最短的一个节点 
			for (j = 1; j <= N; j++) {
				if (!visited[j] && distance[j] != -1 & distance[j] < minDis) {
					minDis = distance[j];
					minIndex = j;
				}
			}
			visited[minIndex] = true;
			//更新distance，
			for (j = 1; j <= N; j++) {
				if (graph[minIndex][j] != -1) { //如果是minIndex节点可到达的节点 
					if (distance[j] == -1) {
						distance[j] = minDis + graph[minIndex][j];
					}
					else {
						distance[j] = minDis+graph[minIndex][j] < distance[j] ? minDis+graph[minIndex][j] : distance[j];
					}
				}
			}
		}
		int res = -1;
		for (i = 1; i <= N; i++) {
			if (distance[i] == -1) { //如果有distance的值为-1，说明没有被遍历到，则说明信号不可达 
				return -1;
			}
			if (distance[i] > res) {
				res = distance[i];
			}
		}
		return res;
	}
};

int main() {
	return 0;
}
