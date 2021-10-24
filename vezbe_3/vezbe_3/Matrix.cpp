#include "Matrix.h"
#include <ostream>
#include <iostream>
#include <iomanip>
using namespace std;
Matrix::Matrix(int n)
{
	for (int i = 0; i < n; i++)
		matrix.push_back(vector<double>(n, 0));
}

vector<double>& Matrix::operator[](int idx)
{
	return matrix[idx];
}

vector<double> Matrix::operator[](int idx) const
{
	return matrix[idx];
}


std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	for (auto row : matrix.matrix)
	{
		for (auto col : row)
			os << setw(5) << col << " ";
		os << endl;
	}
	return os;
}
