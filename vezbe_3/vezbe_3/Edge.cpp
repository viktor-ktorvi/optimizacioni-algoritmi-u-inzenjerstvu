#include "Edge.h"

Edge::Edge(int n1, int n2)
{
	nodes.push_back(n1);
	nodes.push_back(n2);
}

std::ostream& operator<<(std::ostream& os, const Edge& edge)
{
	os << edge.nodes[0] << "_" << edge.nodes[1];
	return os;
}
