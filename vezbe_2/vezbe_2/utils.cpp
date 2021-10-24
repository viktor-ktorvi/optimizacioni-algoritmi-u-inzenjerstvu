#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string> split_string(string line, char delimiter)
{
	vector<string> tokens;

	int prev = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == delimiter)
		{
			tokens.push_back(line.substr(prev, i - prev));
			prev = i;
			while (!isdigit(line[prev])) ++prev;
		}

		if (i == line.length() - 1)
			tokens.push_back(line.substr(prev, i + 1 - prev));
	}

	return tokens;
}

vector<vector<string>> read_csv(string filename, char delimiter)
{
	ifstream fholes(filename);
	string line;
	vector<vector<string>> matrix;

	while (getline(fholes, line))
	{
		matrix.push_back(split_string(line, delimiter));
	}

	fholes.close();

	return matrix;
}

int factorial(int N)
{
	return (int)tgamma(N + 1);
}
