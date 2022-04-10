#pragma once
#include "List.h"
#include <cstdlib>

typedef int index;

class Graph
{
public:
	Graph(int vertCount);
	~Graph();
public:
	bool** adjMatrix;
	List<index> exits;
	List<index> entrances;


	int GetVerticesCount();
	int GetEdgesCount();
private:
	int m_vertices;
	int m_edges;
};



