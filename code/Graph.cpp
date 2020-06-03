/*
 图论 
 */
 
#include <stdio.h>
#include <vector>
using namespace std;

/*图的数据结构
  一个图包含了顶点(vertex)，边(edge)
   
  下面实现的图的边都是权重边 
 */
 
//顶点的数据结构 
typedef struct {
	int val;
	Vertex(): val()
	Vertex(int val): val(val) {}
} Vertex;

//边数据结构 
typedef struct {
	int weight; //权重 
	int index;
	Edge(): weight(), index() {}
	Edge(int weight, int index): weight(weight), index(index);
} Edge;

//邻接矩阵实现的图 
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

