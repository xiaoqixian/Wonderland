#include<iostream>
#include <list>
#include <queue>
using namespace std;

/************************������************************/
class Graph
{
    int V;             // �������
    list<int> *adj;    // �ڽӱ�
    queue<int> q;      // ά��һ�����Ϊ0�Ķ���ļ���
    int* indegree;     // ��¼ÿ����������
public:
    Graph(int V);                   // ���캯��
    ~Graph();                       // ��������
    void addEdge(int v, int w);     // ��ӱ�
    bool topological_sort();        // ��������
};

/************************�ඨ��************************/
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];

    indegree = new int[V];  // ���ȫ����ʼ��Ϊ0
    for(int i=0; i<V; ++i)
        indegree[i] = 0;
}

Graph::~Graph()
{
    delete [] adj;
    delete [] indegree;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); 
    ++indegree[w];
}

bool Graph::topological_sort()
{
    for(int i=0; i<V; ++i)
        if(indegree[i] == 0)
            q.push(i);         // ���������Ϊ0�Ķ������

    int count = 0;             // ��������¼��ǰ�Ѿ�����Ķ����� 
    while(!q.empty())
    {
        int v = q.front();      // �Ӷ�����ȡ��һ������
        q.pop();

        cout << v << " ";      // ����ö���
        ++count;
        // ������vָ��Ķ������ȼ�1��������ȼ�Ϊ0�Ķ�����ջ
        list<int>::iterator beg = adj[v].begin();
        for( ; beg!=adj[v].end(); ++beg)
            if(!(--indegree[*beg]))
                q.push(*beg);   // �����Ϊ0������ջ
    }

    if(count < V)
        return false;           // û�����ȫ�����㣬����ͼ���л�·
    else
        return true;            // ��������ɹ�
}
