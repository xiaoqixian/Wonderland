/*
 LeetCode: 1042.���ڽ�ֲ�� 
 ���Ȿ�����Ǹ�Ⱦɫ����
 ���Ƚ���ͼ���ڽӱ���������ڽӾ���Ļ���ջ�����
 �������еĽڵ㣬��4�ֻ���ȥ�����ڽڵ��Ѿ����˵�?��Ȼ��ѡ��һ�����ϡ�
 */

class Solution {
public:
    vector<int> gardenNoAdj(int N, vector<vector<int>>& paths) {
        //�����ڽӱ�
        vector<int> adj[N];
        for (int i = 0; i < paths.size(); i++) {
            adj[paths[i][0]-1].push_back(paths[i][1] - 1);
            adj[paths[i][1]-1].push_back(paths[i][0] - 1);
        }
        //�������л�԰�����������ڻ�԰��û���ֵ�?
        vector<int> res(N, 0);
        int size;
        for (int i = 0; i < N; i++) {
            int breeds[] = {1,2,3,4};   
            size = adj[i].size();
            for (int j = 0; j < size; j++) {
                if (res[adj[i][j]] != 0) {
                    breeds[res[adj[i][j]] - 1] = 0;
                }
            }
            //���������ɫ������һ������û�б����ڻ�԰��ֲ��Ʒ�ֵ�?��
            for (int k = 0; k < 4; k++) {
                if (breeds[k] != 0) {
                    res[i] = breeds[k];
                    break;
                }
            }
        }
        return res;
    }
};
