#include <vector>
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