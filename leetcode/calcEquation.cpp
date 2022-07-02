/*
 * Leetcode 399.除法求值
 * 数据结构考察：幷查集
 *
 * 解法在注释和../doc/幷查集.md中均有说明
 * 本解法来自于leetcode题解。我写的两次都太烂了，我讲责任归咎在对map的不了解上。
 * 这份代码确实写的美
 */

class Solution {
public:
    int count;
    unordered_map<string, string> parents; // 存储当前结点的父母
    unordered_map<string, double> weights; // 存储 当前结点值/父母值 的结果

    // 返回root以及从a/root的值
    pair <string, double> MyFind(string a){
        if(parents.find(a) == parents.end())
            return {"", -1.0};
        double result = 1.0;
        while(a != parents[a]){
            result *= weights[a]; // result *= a/parent;
            // 路径压缩后还需要更新weights，这里偷懒就不路径压缩了
            a = parents[a];
        }
        return {a, result}; // 返回a的根节点，和a/root的结果
    }
 
    // a_b表示a除以b的结果
    void MyUnion(string a, string b, double a_b){
        pair<string, double> p1 = MyFind(a);
        pair<string, double> p2 = MyFind(b);
        if("" == p1.first || "" == p2.first) return;
        if(p1.first == p2.first) return;
        parents[p1.first] = p2.first; 
        weights[p1.first] = 1/p1.second * a_b * p2.second; // 更新权重
        count--;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 并
        for(int i=0; i<equations.size(); ++i){
            string a = equations[i][0];
            string b = equations[i][1];
            // 并查集初始化
            if(parents.find(a) == parents.end()){
                count++;
                parents[a] = a;
                weights[a] = 1.0;
            }
            if(parents.find(b) == parents.end()){
                count++;
                parents[b] = b;
                weights[b] = 1.0;
            }
            // 并操作
            MyUnion(a, b, values[i]);
        }

        // 查
        vector<double> result;
        for(auto &q : queries){
            string a = q[0];
            string b = q[1];
            pair<string, double> p1 = MyFind(a); // p1.second = a/p1
            pair<string, double> p2 = MyFind(b); // p2.second = b/p2
            if(p1.first != p2.first || "" == p1.first || "" == p2.first){
                result.push_back(-1.0);
            }
            else{
                result.push_back(p1.second/p2.second); // a/b = (a/p1) / (b/p2);
            }
        }
        return result;

    }
};

