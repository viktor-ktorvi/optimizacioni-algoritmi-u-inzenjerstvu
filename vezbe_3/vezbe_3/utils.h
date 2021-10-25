#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <string>
class Matrix;
using namespace std;

bool next_variation_repeating(std::vector<int>& variation, int N);
void get_edges_and_branches(vector<int> variation, int n, vector<vector<int>>& edges, vector<int>& node_branch_count);
Matrix load_cost_matrix(string filename, int height_padding, int width_padding, int size);
#endif // !UTILS_H_
