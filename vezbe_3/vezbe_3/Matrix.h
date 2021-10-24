#ifndef MATRIX_H_
#define MATRIX_H_

#include <vector>
#include <ostream>
using namespace std;

// really should use template
class Matrix
{
private:
	vector<vector<double>> matrix;

public:

	Matrix(int n);

	vector<double>& operator[](int idx);
	vector<double>  operator[](int idx) const;

	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};
#endif // !MATRIX_H_


