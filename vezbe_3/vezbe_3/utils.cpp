#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>
#include "utils.h"
#include "Matrix.h"
using namespace std;

bool next_variation_repeating(vector<int>& variation, int N)
{	
	int carry = 1;
	for (int i = variation.size() - 1; i >= 0; i--)
	{
		variation[i] += carry;
		if (variation[i] == N)
		{
			variation[i] = 0;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
	}

	if (carry == 1)
	{
		cout << endl;
		for (auto x : variation)
			cout << x;
		cout << endl;
	}

	return carry == 0;
}

void get_edges_and_branches(vector<int> variation, int n, vector<vector<int>>& edges, vector<int>& node_branch_count)
{
	vector<int> p_code(variation);

	vector<int> v_nodes(n);
	iota(begin(v_nodes), end(v_nodes), 0); // Fill with 0, 1, ... N - 1


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
}

Matrix load_cost_matrix(string filename, int height_padding, int width_padding, int size)
{
	ifstream cost_file(filename);
	string line;

	Matrix matrix(size);

	int i = 0;
	while (getline(cost_file, line))
	{
		if (i++ < height_padding)
			continue;

		string str_val;
		stringstream line_stream(line);

		int j = 0;
		while (line_stream >> str_val)
		{
			if (j++ < width_padding)
				continue;

			matrix[i - height_padding - 1][j - height_padding - 1] = stod(str_val);
		}
	}

	cost_file.close();

	return matrix;
}


