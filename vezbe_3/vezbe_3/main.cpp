#include <iostream>
#include <vector>

#include "utils.h"
#include "Graph.h"
using namespace std;

const int n = 8;
int main()
{	
	int example_array[n - 2] = { 2, 2, 3, 4, 3, 5 };
	vector<int> p_coding;
	for (int a : example_array) p_coding.push_back(a);
	
	Graph graph(p_coding);

	cout << graph << endl;
}