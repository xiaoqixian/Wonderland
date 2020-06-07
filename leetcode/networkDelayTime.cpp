/*
 Leetcode: 743.�����ӳ�ʱ��
 ���Ȿ��������ڵ�K���������̾��룬��Ҫ���õ��Ͻ�˹�����㷨 
 �������нڵ�ı��Ϊ1��N������Ϊ�˼��ټ������㣬�������������ΪN+1�Ĵ�С����0λ��ʹ�� 
 */ 
 
#include <vector>
#include <string.h>
#include <limits.h> 
using namespace std;
 
class Solution {
public:
	int networkDelayTime(vector<vector<int> >& times, int K, int N) { //times�ṹ[u,v,w]��u���ݵ�v���õ�ʱ��Ϊw 
		//����һ���ڽӾ���
		int graph[N+1][N+1], size = times.size(), i, j;
		memset(graph, -1, sizeof(graph));
		for (i = 0; i < size; i++) {
			graph[times[i][0]][times[i][1]] = times[i][2];
		}
		//����һ������distance��ʾ�����ڵ㵽�ڵ�K����̾���
		int distance[N+1];
		//��ʼ��K�ڵ㵽��ɵ���ڵ����
		for (i = 1; i <= N; i++) {
			distance[i] = graph[K][i];
		}
		distance[K] = 0;
		//����һ������visited��ʾ�ڵ��Ƿ񱻷��ʹ�
		bool visited[N+1];
		memset(visited, false, sizeof(visited));
		visited[K] = true;
		
		/*���ű������ڵ�K֮���N-1���ڵ� 
		  ��ÿ�α����ж�Ҫ�ҵ���ǰδ���ʵ���ڵ�K����Ľڵ㡣��ȥ�Ƚ�����Ľڵ㵽ĳ�ڵ���K�ڵ�ֱ�ӵ���ľ����С�����и��¡�
		  �����K���пɵ���Ľڵ㶼��������û�з��ʵĽڵ㣬��˵���ýڵ��ź��޸´�� 
		 */
		int minDis, minIndex;
		//i���ڱ���N-1�Σ���ʵ������ 
		for (i = 1; i < N; i++) {
			minDis = INT_MAX;
			minIndex = 1;
			//�ҵ����пɵ���ڵ�����̵�һ���ڵ� 
			for (j = 1; j <= N; j++) {
				if (!visited[j] && distance[j] != -1 & distance[j] < minDis) {
					minDis = distance[j];
					minIndex = j;
				}
			}
			visited[minIndex] = true;
			//����distance��
			for (j = 1; j <= N; j++) {
				if (graph[minIndex][j] != -1) { //�����minIndex�ڵ�ɵ���Ľڵ� 
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
			if (distance[i] == -1) { //�����distance��ֵΪ-1��˵��û�б�����������˵���źŲ��ɴ� 
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
