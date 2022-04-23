#pragma once
#include "List.h"
#include "Edge.h"
#include "Table.h"
#include <cstdlib>


class Graph
{
public:
	Graph(int vertCount);
	~Graph();
public:
	bool** adjMatrix;
	BYTE** trapMatrix;					// TODO: replace trap matrix by trap table
	Table<Edge, BYTE> traps;
	char entrance = -1;
	List<BYTE> exits;	

	BYTE GetVerticesCount();
private:
	BYTE m_vertices;
};



