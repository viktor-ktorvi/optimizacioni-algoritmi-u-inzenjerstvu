#ifndef UTILS_H_
#define UTILS_H_
#include <vector>
#include <string>
using namespace std;

vector<string> split_string(string line, char delimiter);
vector<vector<string>> read_csv(string filename, char delimiter);
int factorial(int N);

#endif 