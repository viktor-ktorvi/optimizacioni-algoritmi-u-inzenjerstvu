#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <ostream>
class Node;
class Edge;

class Graph
{
private:
	std::vector<Edge*> edges;
	std::vector<Node*> nodes;

public:
	Graph(std::vector<int> p_coding);
	
	friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
};

#endif // !GRAPH_H_

