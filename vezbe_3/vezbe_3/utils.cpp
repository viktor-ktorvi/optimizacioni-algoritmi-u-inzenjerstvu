#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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

	return carry == 0;
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


