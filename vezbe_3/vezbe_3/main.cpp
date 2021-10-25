#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <chrono>
#include <algorithm>

#include "utils.h"
#include "Graph.h"
#include "Matrix.h"
using namespace std;

const string filename = "tabela Z3.txt";
const int height_padding = 2;
const int width_padding = 2;
const int n = 10;
int main()
{	
	Matrix cost_matrix = load_cost_matrix(filename, height_padding, width_padding, n);
	//cout << cost_matrix;


	/*int example_array[n - 2] = { 2, 2, 3, 4, 3, 5 };
	vector<int> p_coding;
	for (int a : example_array) p_coding.push_back(a);*/

	vector<int> variation(n - 2, 0);

	int iter_counter = 0;
	int num_graphs = (int)pow((double)n, (double)(n - 2));
	double smallest_cost = -1;
	vector<int> best_variation;

	do {
		vector<int> p_code(variation);

		vector<int> v_nodes(n);
		iota(begin(v_nodes), end(v_nodes), 0); // Fill with 0, 1, ... N - 1

		vector<vector<int>> edges(n - 1, vector<int>(2, 0));
		vector<int> node_branch_count(n, 0);

		int i = 0;
		while (p_code.size() > 0)
		{
			sort(v_nodes.begin(), v_nodes.end());
			int j;
			for (j = 0; find(p_code.begin(), p_code.end(), v_nodes[j]) != p_code.end(); j++);

			edges[i][0] = p_code[0];
			edges[i][1] = v_nodes[j];

			node_branch_count[p_code[0]] += 1;
			node_branch_count[v_nodes[j]] += 1;

			i++;

			p_code.erase(p_code.begin());
			v_nodes.erase(v_nodes.begin() + j);
		}

		edges[n - 2][0] = v_nodes[0];
		edges[n - 2][1] = v_nodes[1];

		node_branch_count[v_nodes[0]] += 1;
		node_branch_count[v_nodes[1]] += 1;


		//for (int i = 0; i < edges.size(); i++)
		//{
		//	cout << edges[i][0] << " " << edges[i][1];
		//	if (i != edges.size() - 1)
		//		cout << " -- ";
		//}
		//cout << endl;

		double edge_cost = 0.0;
		for (auto edge : edges)
		{
			edge_cost += cost_matrix[edge[0]][edge[1]];
		}

		double node_cost = 0.0;
		for (auto branch_num : node_branch_count)
		{
			if (branch_num >= 4)
				node_cost += 150 * (branch_num - 3);
		}


		if (smallest_cost == -1 || smallest_cost > edge_cost + node_cost)
		{
			smallest_cost = edge_cost + node_cost;
			best_variation = variation;
		}

		++iter_counter;
		if (iter_counter % 10000 == 0)
			cout << "Progress: " << (double)iter_counter / (double)num_graphs * 100 << " % of " << num_graphs << "Smallest cost = " << smallest_cost << '\r';

	} while (next_variation_repeating(variation, variation.size()));


	cout << "Smallest cost = " << smallest_cost << endl;
	for (auto v : best_variation)
		cout << v;
}