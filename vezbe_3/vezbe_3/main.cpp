#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <chrono>

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
	cout << cost_matrix;

	vector<int> variation(n - 2, 0);
	double min_cost = -1;
	Graph min_cost_graph(vector<int>(1, 0), cost_matrix);	// empty basicaly
	
	int counter = 0;
	int num_graphs = (int)pow((double)n, (double)(n - 2));
	do
	{
		auto t1 = chrono::high_resolution_clock::now();

		Graph graph(variation, cost_matrix);

		auto t2 = chrono::high_resolution_clock::now();

		chrono::duration<double, std::milli> ms_double = t2 - t1;

		cout << "Konstruktor " << ms_double.count() << " ms" << endl;


		t1 = chrono::high_resolution_clock::now();
		double cost = graph.edgeCost() + graph.nodeCost();
		t2 = chrono::high_resolution_clock::now();
		ms_double = t2 - t1;
		cout << "cost " << ms_double.count() << " ms" << endl;

		t1 = chrono::high_resolution_clock::now();
		if (cost < min_cost || min_cost == -1)
		{
			min_cost = cost;
			min_cost_graph = graph;
		}
		t2 = chrono::high_resolution_clock::now();
		ms_double = t2 - t1;
		cout << "if " << ms_double.count() << " ms" << endl;

		++counter;
		if (counter % 10000 == 0)
			cout << "Progress: " << (double)counter / (double)num_graphs * 100 << " % of " << num_graphs << "Min cost = " << min_cost << '\r';

		if (counter == 5) break;
	}while (next_variation_repeating(variation, n - 2));

	cout << endl;
	cout << "Min cost = " << min_cost << endl;
	cout << "Min cost graph:\n" << min_cost_graph;

}