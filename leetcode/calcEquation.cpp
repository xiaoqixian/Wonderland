/*
 ���ˣ�ͨ������һ������ͼ������ͼ�ıߴӷ���ָ���ĸ���ߵ�Ȩֵ����Ϊ����Ľ������Ȼ���򲢲������ǵ���ģ�����˫��ģ�
 �������������Ȩֵ��һ����
 ��ô��Ҫ����ĳ���������̣�����Ҫ�ҵ��ӷ��ӵ���ĸ��·����������·��Ȩֵ��ˡ�����˵�������κ�·�������ս������һ���ġ�
 ������Ѱ�����·��������Ҫ�ˡ�

 ���������˵���ص�������ι������ͼ����������ڴ�ʹ�õĻ�������ʹ��һ��map��Ӧÿ�������ĳ��ȣ����������ھ���Ȩֵ������
 Ҳ��Ҫһ��map����ʾ������������map��Ƕ�ס�����ȨֵҪ��double����ʾ�������֪���ڴ�϶��ܴ�
 */


class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        map<string, map<string, double>> graph;
        for (int i = 0; i < equations.size(); i++) {
            if (graph.find(equations[i][0]) == graph.end()) {//˵����graph�������������
                map<string, double> mole_edge;//���ӱ�
                graph.insert(pair<string, map<string, double>>(equations[i][0], &new_edge));
                new_edge.insert(pair<string, double>(equations[i][1], values[i]));
            }
            else {
                graph[equations[i][0]].insert(pair<string, double>(equations[i][1], values[i]));
            }
            if (graph.find(equations[i][1]) == graph.end()) {
                map<string, double> deno_edge;//��ĸ��
                graph.insert(pair<string, map<string, double>>(equations[i][1], &deno_edge));
                deno_edge.insert(pair<string, double>(equations[i][0], 1/values[i]));
            }
            else {
                graph[equations[i][1]].insert(pair<string, double>(equations[i][0], 1/values[i]));
            }
        }
        
        /*����queries�������ʽ��������graph��������Ҳ����ı����϶��Ǽ��㲻�����ģ���Ϊ�Ҳ����κι���
          ��Σ�Ҳ���ܴ���������������ɵ�ͼ�����Ա����ܹ��ҵ�һ��·����
         */
        
    }
};
