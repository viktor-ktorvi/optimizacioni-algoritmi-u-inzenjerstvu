#include <vector>
#include <iostream>
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

	return carry == 0;
}

vector<int> make_edge(int n1, int n2)
{
	vector<int> edge(2);
	edge[0] = n1;
	edge[1] = n2;

	return edge;
}

void print_edges(vector<vector<int>> edges)
{
	for (int i = 0; i < edges.size(); i++)
	{
		cout << edges[i][0] << " " << edges[i][1];

		if (i != edges.size() - 1)
			cout << " -- ";
	}
	
	cout << endl;
}