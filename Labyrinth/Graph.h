#pragma once
#include <cstdlib>

class Graph
{
public:
	Graph(int vertCount);
	~Graph();
public:
	bool** adjMatrix;

	int GetVerticesCount();
	int GetEdgesCount();
private:
	int m_vertices;
	int m_edges;
};



