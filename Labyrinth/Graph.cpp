#include "Graph.h"
#include <iostream>

Graph::Graph(int vertCount)
{
	m_vertices = vertCount;
	bool** ppRow = (bool**)malloc(vertCount * sizeof(bool*)); //hold pointers to rows
	for (int i = 0; i < vertCount; i++)
	{
		ppRow[i] = (bool*)malloc(vertCount * sizeof(bool));
		for (int j = 0; j < vertCount; j++)
			ppRow[i][j] = false;
	}
	adjMatrix = ppRow;

	traps = Table<Edge, BYTE>();
}

Graph::~Graph()
{
	int sz = this->m_vertices;
	for (int i = 0; i < m_vertices; i++)
	{
		free(adjMatrix[i]);
	}
	free(adjMatrix);
}

BYTE Graph::GetVerticesCount()
{
	return m_vertices;
}