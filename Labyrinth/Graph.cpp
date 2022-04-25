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
}

Graph::~Graph()
{
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

BYTE Graph::DFS(Stack<BYTE>* pStack, bool* aVisited, unsigned short* pLen)
{
	if (pStack->isEmpty())
		return 255;

	BYTE vert = pStack->Get();
	aVisited[vert] = true;

	for (BYTE nextVert = 0; nextVert < m_vertices; nextVert++)
	{
		if (adjMatrix[vert][nextVert] && !aVisited[nextVert])
		{
			for (int i = 0; i < this->exits.size(); i++)
			{
				if (this->exits[i] == nextVert)
					return nextVert;
			}
			
			(*pLen)++;
			pStack->Push(nextVert);
			return DFS(pStack, aVisited, pLen);
		}
	}
	(*pLen)--;
	pStack->Pop();
	return DFS(pStack, aVisited, pLen);
}

BYTE Graph::GetClosestExit()
{
	int nExits = exits.size();
	Pair<BYTE, unsigned short>* aPairs = (Pair<BYTE, unsigned short>*)malloc(this->exits.size() * sizeof(Pair<BYTE, unsigned int>));
	char* exitdata = (char*)malloc(4 + exits.size());
	exits.CopyData(exitdata);
	for (int i = 0; i < nExits; i++)
	{
		unsigned short len = 1;
		bool* aVisited = (bool*)malloc(m_vertices);
		ZeroMemory(aVisited, m_vertices);
		Stack<BYTE> stack(m_vertices);
		stack.Push(entrance);
		BYTE exit = DFS(&stack, aVisited, &len);
		aPairs[i] = Pair<BYTE, unsigned short>{exit, len};
		free(aVisited);
		exits.Remove(exit);
	}
	exits.~List();
	exits = *(new List<BYTE>(exitdata));
	unsigned short minLen = aPairs[0].p2;
	BYTE closestExit = aPairs[0].p1;
	for (int i = 1; i < exits.size(); i++)
	{
		if (aPairs[i].p2 < minLen)
		{
			minLen = aPairs[i].p2;
			closestExit = aPairs[i].p1;
		}
	}
	free(exitdata);
	free(aPairs);
	return closestExit;
}