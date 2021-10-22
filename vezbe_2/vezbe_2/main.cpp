#include <iostream>
#include <fstream>
#include <string>

#include "examples.h"
using namespace std;

const char delimiter = ',';

int main() 
{

	// TODO napraviti f-ju za citanje csv fajla

	ifstream fholes("holes.csv");
	string line;
	while (getline(fholes, line))
	{
		cout << line << endl;
	}

	// TODO napraviti f-ju za parsiranje linije

	int prev = 0;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == delimiter)
		{
			cout << line.substr(prev, i - prev) << endl;
			prev = i;
			while (!isdigit(line[prev])) ++prev;
		}
		
		if (i == line.length() - 1)
			cout << line.substr(prev, i + 1 - prev) << endl;
	}


	fholes.close();
}