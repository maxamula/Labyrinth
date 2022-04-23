#pragma once
#include <windows.h>

class Edge;
bool CompareEdges(Edge e1, Edge e2);

class Edge
{
public:
	Edge();
	Edge(BYTE v1, BYTE v2);
	~Edge();
public:
	BYTE v1, v2;
};


