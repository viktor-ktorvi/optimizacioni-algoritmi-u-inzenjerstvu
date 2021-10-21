#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include "examples.h"

void permutations_example(int N)
{
	std::vector<int> v(N); // vector with 100 ints.
	std::iota(std::begin(v), std::end(v), 1); // Fill with 0, 1, ..., 99.

	do
	{
		for (auto w : v)
		{
			std::cout << w;
		}
		std::cout << std::endl;
	} while (std::next_permutation(v.begin(), v.end()));
}