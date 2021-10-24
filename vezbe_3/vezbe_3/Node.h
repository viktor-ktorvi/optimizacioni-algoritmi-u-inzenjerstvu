#ifndef NODE_H_
#define NODE_H_

class Node
{
private:
	int edge_num;

public:
	Node(int edge_num);
	Node();

    int getEdgeNum() { return edge_num;}

    Node& operator++()
    {
        edge_num++;
        return *this;
    }
    
    Node operator++(int)
    {
        Node tmp(*this);
        edge_num++;
        return tmp;
    }
};

#endif // !NODE_H_

