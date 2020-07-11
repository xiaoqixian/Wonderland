/*
 Leetcode: 310.��С�߶��� 

 ��һ�ַ����������ƽ�
 ��ô�����ת�����˴�ͼ��һ�ڵ��ҵ����߶ȡ�������Խ���Dijkstra�㷨����Dijkstra�㷨��ֻҪ������·����Ȩ��Ϊ1
 ��ô�Ϳ����ҵ����·�����·����

 �ڶ��ַ�������������
 ������ʵ������������ı�ʽ�����ǲ�����Сͼ��ֱ��ʣ��1��2���㣬return��
    Ȼ��������ı�ʽ�����£�

    ����Ϊ����ͼ������ɾ���ĵ������Ϊ1�ĵ㡣
    ���ⲻ��һ��һ����ɾ�����Ϊ1�ĵ㣬��Ӧ��һ��ѭ���У�һ����ɾ�����Ϊ1�ĵ㣬ʹ����ͬ�����ٶ���Сͼ��ֱ��ʣ      ��<=2����Ϊֹ��֮������ô˵����Ϊ������ڳ���2���㣬��һ������3�������һ����ȸ�С�ĵ㣬�������ս������
    ����2�ġ�

 ʵ�ʴ����з�Ϊ����ѭ������һ��ѭ����ֱ�����ս��С�ڵ���2���ڶ���ѭ������edges���ҵ����Ϊ1�ı߲�ɾ����
 */

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) {
            return {0};
        }
        if (n == 2) {
            return {0,1};
        }
        /*����Ҫ��ʼ��һ��ͼgraph�����indegree��
          graph��һ����ά��vector������n�У�graph[i]��vector�洢����i�����������е�
          indegree����һ��һά���飬����������ʾ��Ӧ������
         */
        vector<int> v; //������ʼ��graph����ʵ���ô�
        vector<vector<int>> graph(n, v);
        vector<int> indegree(n, 0);
        for (int i = 0; i < edges.size(); i++) {
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
            indegree[edges[i][0]]++;
            indegree[edges[i][1]]++;
        }

        int count = 0; //count��ʾindegree�����Ϊ1������
        queue<int> q; //q�����洢��ǰ���Ϊ1�ĵ�
        //��һ�μ���indegree�����Ϊ1������
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 1) {
                count++;
                q.push(i);
            }
        }

        while (n > 2) {
            n -= count;
            while (count--) {
                int tmp = q.front();
                q.pop();
                indegree[tmp] = 0;
                /*
                 ����ÿһ�����Ϊ1�ĵ㣬��ɾ��ʱ��Ҫ�������£�
                 1. �����������˵���ɾ���Լ�
                 2. ����ȼ�1
                 */
                for (int i = 0; i < graph[tmp].size(); i++) { //������Ϊgraph�в���ʵ��ɾ���㣬������Ҫ���ݴ�С�ж�
                    if (indegree[graph[tmp][i]] != 0) {
                        indegree[graph[tmp][i]]--;
                        if (indegree[graph[tmp][i]] == 1) {
                            q.push(graph[tmp][i]);
                        }
                    }
                }
            }
            count = q.size();
        }
        vector<int> result;
        while (!q.empty())
        {
            result.push_back(q.front());
            q.pop();
        }
        return result;
    }
};
