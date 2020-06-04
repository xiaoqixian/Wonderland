/*
 Leetcode: 207.�n�̱� 
 */ 
 
/*
 �ǳ�������ж�����ͼ���Ƿ��бջ����㷨��
 �ж�����ͼ���Ƿ��бջ��ľ�����������������������

 ����dfs��bfs����ͼ�����нڵ㣬ɾ������û��ǰ���Ľڵ�����ͼ��Ϊ�յĻ���˵��ͼ�д��ڻ��ˡ�����ʹ��bfs
 
 
 */

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //�Ƚ����нڵ����һ�飬�ٱ���û��ǰ���Ľڵ�ĺ�����ֱ��Ϊ��
        int indegree[numCourses];//ä��numCourses�ǿγ̵ı��λ��0~numCourses-1,��˿��������жϽڵ�����
        memset(indegree, 0, sizeof(indegree));
        list<int> l[numCourses]; //ʹ��һ�����Կ�����ϣ���list������Ѹ��Ѱַ 
        queue<int> q;
        int i;
        int count = 0;
        int size = prerequisites.size();
        for (i = 0; i < size; i++) {
            indegree[prerequisites[i][1]]++;
            l[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }
        for (i = 0; i < numCourses; i++) {
            if (!indegree[i]) {
                q.push(i);
                count++;
            }
        }
        int node;
        list<int>::iterator beg;
        while (!q.empty()) {
            node = q.front();
            q.pop();
            beg = l[node].begin();
            for( ; beg!=l[node].end(); ++beg) {
                if(!(--indegree[*beg])) {
                    q.push(*beg);   // �����Ϊ0������ջ
                    count++;
                }
            }
        }
        if (count == numCourses) {
            return true;
        }
        return false;
    }
};
