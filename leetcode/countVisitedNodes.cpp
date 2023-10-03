// Date: Tue Oct 03 10:48:30 2023
// Mail: lunar_ubuntu@qq.com
// Author: https://github.com/xiaoqixian

#include <vector>
#include <stack>
class Solution {
public:
    std::vector<int> countVisitedNodes(std::vector<int>& edges) {
        //像这类单向单边图都可以看成由多个带尾巴的环组成
        //如果开始的结点在环上，则最终的结果就是环的长度
        //如果不在环上，则最终的结果就是环的长度加上到环的距离

        //构建环过程：
        //首先找到所有入度为零的结点
        //根据递归可以很好地找到这些节点到环的距离
        //但由于环的长度可能非常大，为了避免溢出，使用栈来进行操作
        //首先维护一个visited访问过位图
        //对于每一个节点，找到其下一个节点后将其入栈
        //如果下一个节点j已经访问过，则说明已经形成环，开始出栈
        //while循环中不断出栈节点直到遇到j，说明环结点已经全部出栈
        //继续出栈环尾巴，此时到环的距离逐一增长

        const int n = edges.size();
        std::vector<int> res(n, 0), degree(n, 0);
        for (int i = 0; i < n; i++) {
            degree[i]--;
            degree[edges[i]]++;
        }

        std::vector<bool> visited(n, false);
        auto visit = [&](const int start) {
            if (visited[start]) return;
            std::stack<int> st;
            st.push(start);
            while (!st.empty()) {
                const int curr = st.top();
                if (!visited[curr]) {
                    visited[curr] = true;
                    st.push(edges[curr]);
                    continue;
                }

                //如果遇到过这个节点，有两种情况
                //第一种是这是一个环中的节点，且这个环还没有被发掘
                //则需要通过循环出栈来找出环
                //第二种是这是此前的循环中访问过的节点，只是恰巧有节点
                //指向了其，则只需要将栈中所有节点都赋值即可。
                //由于被发掘过的节点会直接将res中的值修改，且保证大于0
                //所以可以通过这一点来区分两种情况
                if (res[curr]) {
                    st.pop();
                    int len = res[curr];
                    while (!st.empty()) {
                        res[st.top()] = ++len;
                        st.pop();
                    }
                } else {
                    std::vector<int> ring_nodes;
                    do {
                        ring_nodes.push_back(st.top());
                        st.pop();
                    } while (curr != st.top());
                    const int ring_length = ring_nodes.size();
                    for (const int nd: ring_nodes) {
                        res[nd] = ring_length;
                    }
                    //此时栈顶还保留着进入此else语句时的curr
                    //因此可以将尾部的res先不进行处理
                    //则在下一个循环中进入if语句，从而避免代码重复
                }
            }
        };

        //由于可能存在无尾巴的环
        //所以在访问过零入度结点之后还要访问
        //入度=出度的结点
        for (int i = 0; i < n; i++) {
            if (degree[i] < 0) visit(i);
        }
        for (int i = 0; i < n; i++) {
            if (!degree[i] && !visited[i])
                visit(i);
        }
        return res;
    }
};
