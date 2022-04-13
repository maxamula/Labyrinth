#include "Graph.h"

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

	int** trapMatrix = (int**)malloc(vertCount * sizeof(int*)); //hold pointers to rows
	for (int i = 0; i < vertCount; i++)
	{
		trapMatrix[i] = (int*)malloc(vertCount * sizeof(int));
		for (int j = 0; j < vertCount; j++)
			trapMatrix[i][j] = 1 + rand() % 40;
	}
	this->trapMatrix = trapMatrix;

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

int Graph::GetVerticesCount()
{
	return m_vertices;
}