#ifndef EDGE_H_
#define EDGE_H_

#include <vector>
#include <ostream>

class Edge
{
private:
	std::vector<int> nodes;
public:
	Edge(int n1, int n2);

	int& operator[](int idx);
	int  operator[](int idx) const;

	friend std::ostream& operator<<(std::ostream& os, const Edge& edge);
};



#endif // !1
