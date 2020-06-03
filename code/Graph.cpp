/*
 ͼ�� 
 */
 
#include <stdio.h>
#include <vector>
using namespace std;

/*ͼ�����ݽṹ
  һ��ͼ�����˶���(vertex)����(edge)
   
  ����ʵ�ֵ�ͼ�ı߶���Ȩ�ر� 
 */
 
//��������ݽṹ 
typedef struct {
	int val;
	Vertex(): val()
	Vertex(int val): val(val) {}
} Vertex;

//�����ݽṹ 
typedef struct {
	int weight; //Ȩ�� 
	int index;
	Edge(): weight(), index() {}
	Edge(int weight, int index): weight(weight), index(index);
} Edge;

//�ڽӾ���ʵ�ֵ�ͼ 
class MatrixGraph {
private:
	vector<Vertex*> vertices;
	vector<vector<int> > matrix;
	
public:
	MatrixGraph() {
		
	}
	void addVertex(int val);
	void link(int vertex1, int vertex2, int weight);
};

