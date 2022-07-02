/*
 Leetcode: 207.課程表 
 */ 
 
/*
 非常经典的判断有向图中是否有闭环的算法题
 判断有向图中是否有闭环的经典做法就是利用拓扑排序

 利用dfs或bfs遍历图中所有节点，删除所有没有前驱的节点后如果图不为空的话就说明图中存在环了。本题使用bfs
 
 
 */

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        //先将所有节点遍历一遍，再遍历没有前驱的节点的后驱，直到为空
        int indegree[numCourses];//盲猜numCourses们课程的标号位于0~numCourses-1,因此可以用来判断节点的入度
        memset(indegree, 0, sizeof(indegree));
        list<int> l[numCourses]; //使用一个可以看做哈希表的list数组来迅速寻址 
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
                    q.push(*beg);   // 若入度为0，则入栈
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
