#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <string>
class Matrix;
using namespace std;

bool next_variation_repeating(std::vector<int>& variation, int N);
Matrix load_cost_matrix(string filename, int height_padding, int width_padding, int size);
#endif // !UTILS_H_
