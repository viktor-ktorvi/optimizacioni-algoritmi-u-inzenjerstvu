#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include "examples.h"
#include "utils.h"
using namespace std;

const char delimiter = ',';
const int N = 4;

int main() 
{
	vector<vector<string>> matrix = read_csv("holes.csv", delimiter);
	vector<vector<double>> values;
	
	// convert to double and keep only x and y, not the row number
	for (int i = 0; i < matrix.size(); i++)
	{
		vector<double> row;
		for (int j = 1; j < matrix[i].size(); j++)
			row.push_back(stod(matrix[i][j]));
		
		values.push_back(row);
	}

	vector<int> permutation(N); // vector with N ints.
	iota(begin(permutation), end(permutation), 0); // Fill with 0, 1, ... N - 1

	double min_dist = -1;
	vector<double> prev_hole;
	vector<int> best_perm;
	do
	{
		double perm_dist = 0;
		// napraviti f-ju
		for (int i = 1; i < permutation.size(); i++)
		{
			// |x_i - x_i1| + |y_i - y_i1|
			perm_dist += abs(values[permutation[i]][0] - values[permutation[i - 1]][0]) + abs(values[permutation[i]][1] - values[permutation[i - 1]][1]);
		}

		if (perm_dist < min_dist || min_dist == -1)
		{
			min_dist = perm_dist;
			best_perm = permutation;
		}

	} while (next_permutation(permutation.begin(), permutation.end()));
	
	cout << "Shortest distance = " << min_dist << "\nBest permutation:\n";
	for (auto p : best_perm)
		cout << p << ": (" << ;
	// TODO ispisati redni broj pa (x, y) i proveriti za manje N pa preci da vece
}