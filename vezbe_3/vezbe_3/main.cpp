#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include "utils.h"
#include "examples.h"
using namespace std;

const int n = 8;
int main()
{	
	int example_array[n - 2] = { 2, 2, 3, 4, 3, 5 };
	vector<int> p_coding;
	for (int a : example_array) p_coding.push_back(a);

	vector<int> v_nodes(n);
	iota(begin(v_nodes), end(v_nodes), 0); // Fill with 0, 1, ... N - 1

	vector<vector<int>> edges;

	for (int i = 0; i < n - 2; i++)
	{
		sort(v_nodes.begin(), v_nodes.end());
		int j;
		for (j = 0; find(p_coding.begin(), p_coding.end(), v_nodes[j]) != p_coding.end(); j++);

		
		edges.push_back(make_edge(v_nodes[j], p_coding[0]));

		v_nodes.erase(v_nodes.begin() + j);
		p_coding.erase(p_coding.begin());
	}

	edges.push_back(make_edge(v_nodes[0], v_nodes[1]));
	
	print_edges(edges);
}