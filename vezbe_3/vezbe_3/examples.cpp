#include <iostream>
#include <vector>
#include "utils.h"
using namespace std;
void variations_repeating(int N, int K)
{
	int counter = 0;
	vector<int> variations(K, 0);
	do {
		for (int v : variations)
			cout << v << ' ';
		cout << endl;
		counter++;
	} while (next_variation_repeating(variations, N));

	cout << "Counter = " << counter << "\nN ^ K = " << (int)pow((double)N, (double)K);
}