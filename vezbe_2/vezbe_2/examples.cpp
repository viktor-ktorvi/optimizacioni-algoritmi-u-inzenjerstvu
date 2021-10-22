#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

#include "examples.h"

void permutations_example(int N)
{
	std::vector<int> v(N); // vector with N ints.
	std::iota(std::begin(v), std::end(v), 1); // Fill with 1, 2, ... N

	do
	{
		for (auto element : v)
		{
			std::cout << element;
		}
		std::cout << std::endl;
	} while (std::next_permutation(v.begin(), v.end()));
}