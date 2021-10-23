#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>

#include "examples.h"
#include "utils.h"
using namespace std;

const char delimiter = ',';
const int N = 8;

int main() 
{	
	vector<vector<string>> matrix = read_csv("holes.csv", delimiter);
	
	// convert to double and keep only x and y, not the row number
	vector<vector<double>> values;

	for (int i = 0; i < matrix.size(); i++)
	{
		vector<double> row;
		for (int j = 1; j < matrix[i].size(); j++)
			row.push_back(stod(matrix[i][j]));

		values.push_back(row);
	}


	auto t1 = chrono::high_resolution_clock::now();
	vector<int> permutation(N); // vector with N ints.
	iota(begin(permutation), end(permutation), 0); // Fill with 0, 1, ... N - 1

	double min_dist = -1;
	vector<double> prev_hole;
	vector<int> best_perm;
	
	int counter = 0;
	int num_permutations = factorial(N);

	do
	{
		double perm_dist = 0;
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

		++counter;
		if (counter % 1000000 == 0)
			cout << "Progress: " << (double)counter / (double)num_permutations * 100 << " % of " << num_permutations << '\r';

	} while (next_permutation(permutation.begin(), permutation.end()));

	cout << "Finished searching " << num_permutations << " permutations!" << endl;

	auto t2 = chrono::high_resolution_clock::now();

	// measure execution time
	chrono::duration<double, std::milli> ms_double = t2 - t1;
	cout << "\nDuration of the search for N = " << N << ": " << ms_double.count() << " ms" << endl;
	
	cout << "\nShortest distance = " << min_dist << "\nBest permutation:\n";
	for (auto p : best_perm)
		cout << p + 1 << ": (" << values[p][0] << ", " << values[p][1] << ")" << endl;

}