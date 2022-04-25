#pragma once
#include "List.h"
#include "Edge.h"
#include "Table.h"
#include "Stack.h"
#include <cstdlib>


class Graph
{
public:
	Graph(int vertCount);
	~Graph();
public:
	bool** adjMatrix;
	Table<Edge, BYTE> traps;
	List<BYTE> exits;
	char entrance = -1;	

	BYTE GetVerticesCount();
	BYTE GetClosestExit();
private:
	BYTE m_vertices;

	BYTE DFS(Stack<BYTE>* pStack, bool* aVisited, unsigned short* pLen);
};



