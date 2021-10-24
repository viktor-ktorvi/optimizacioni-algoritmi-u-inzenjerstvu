#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <numeric>
#include <algorithm>
#include <ostream>

using namespace std;
Graph::Graph(vector<int> p_coding)
{	
	int n = p_coding.size() + 2;
	nodes = vector<Node*>(n);

	vector<int> v_nodes(n);
	iota(begin(v_nodes), end(v_nodes), 0); // Fill with 0, 1, ... N - 1

	for (int i = 0; i < n - 2; i++)
	{
		sort(v_nodes.begin(), v_nodes.end());
		int j;
		for (j = 0; find(p_coding.begin(), p_coding.end(), v_nodes[j]) != p_coding.end(); j++);


		edges.push_back(new Edge(v_nodes[j], p_coding[0]));

		v_nodes.erase(v_nodes.begin() + j);
		p_coding.erase(p_coding.begin());
	}

	edges.push_back(new Edge(v_nodes[0], v_nodes[1]));
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
