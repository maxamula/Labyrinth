#include "Edge.h"


Edge::Edge()
{
	this->v1 = 0;
	this->v2 = 0;
}

Edge::Edge(BYTE v1, BYTE v2)
{
	this->v1 = v1;
	this->v2 = v2;
}

Edge::~Edge()
{

}

bool CompareEdges(Edge e1, Edge e2)
{
	if (e1.v1 == e2.v1 && e1.v2 == e2.v2)
		return true;
	return false;
}