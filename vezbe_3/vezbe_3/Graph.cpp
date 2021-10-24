#include <numeric>
#include <algorithm>
#include <ostream>

#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Matrix.h"

using namespace std;
Graph::Graph(vector<int> p_coding, Matrix cost_matrix): cost_matrix(cost_matrix)
{	
	int n = p_coding.size() + 2;
	for (int i = 0; i < n; i++)
		nodes.push_back(new Node(0));

	vector<int> v_nodes(n);
	iota(begin(v_nodes), end(v_nodes), 0); // Fill with 0, 1, ... N - 1

	for (int i = 0; i < n - 2; i++)
	{
		sort(v_nodes.begin(), v_nodes.end());
		int j;
		for (j = 0; find(p_coding.begin(), p_coding.end(), v_nodes[j]) != p_coding.end(); j++);


		edges.push_back(new Edge(v_nodes[j], p_coding[0]));
		++(*nodes[v_nodes[j]]);
		++(*nodes[p_coding[0]]);

		v_nodes.erase(v_nodes.begin() + j);
		p_coding.erase(p_coding.begin());
	}

	edges.push_back(new Edge(v_nodes[0], v_nodes[1]));
	++(*nodes[v_nodes[0]]);
	++(*nodes[v_nodes[1]]);
}

// Hopefully it's a good deep copy constructor
//Graph::Graph(const Graph& g): cost_matrix(g.cost_matrix)
//{
//	for (auto edge_ptr : g.edges)
//		edges.push_back(new Edge(*edge_ptr));
//
//	for (auto node_ptr : g.nodes)
//		nodes.push_back(new Node(*node_ptr));
//}


double Graph::edgeCost()
{
	double edge_cost = 0.0;
	for (auto edge_ptr : edges)
		edge_cost += cost_matrix[(*edge_ptr)[0]][(*edge_ptr)[1]];

	return edge_cost;

}

double Graph::nodeCost()
{
	double node_cost = 0.0;
	for (auto node_ptr : nodes)
	{
		if (node_ptr->getEdgeNum() >= 4)
			node_cost += (node_ptr->getEdgeNum() - 3) * 150;
	}

	return node_cost;
}

std::ostream& operator<<(std::ostream& os, const Graph& graph)
{
	for (int i = 0; i < graph.edges.size(); i++)
	{
		os << *graph.edges[i];
		if (i != graph.edges.size() - 1)
			os << " -- ";
	}

	return os;
}
