#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <ostream>
#include "Matrix.h"

using namespace std;

class Node;
class Edge;

class Graph
{
private:
	std::vector<Edge*> edges;
	std::vector<Node*> nodes;
	Matrix cost_matrix;

public:
	Graph(std::vector<int> p_coding, Matrix cost_matrix);
	//Graph(const Graph& g);

	double edgeCost();
	double nodeCost();
	
	friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

#endif // !GRAPH_H_

