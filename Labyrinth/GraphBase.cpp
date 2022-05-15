#include "GraphBase.h"

GraphBase::GraphBase(BYTE verts)
{
	m_vertices = verts;
	adjMat = (bool**)malloc(verts*sizeof(bool*));
	for (int i = 0; i < verts; i++)
	{
		adjMat[i] = (bool*)malloc(verts);
		ZeroMemory(adjMat[i], verts);
	}	
}

GraphBase::~GraphBase()
{
	for (int i = 0; i < m_vertices; i++)
	{
		free(adjMat[i]);
	}
	free(adjMat);
}

void GraphBase::DFS(bool (*callback)(BYTE vert), Stack<BYTE>* pSequence, bool* aUsed)
{
	if (pSequence->isEmpty())
		return;

	BYTE vert = pSequence->Get();
	aUsed[vert] = true;

	if (!callback(vert))
		return;

	for (BYTE nextVert = 0; nextVert < m_vertices; nextVert++)
	{
		if (adjMat[vert][nextVert] && !aUsed[nextVert])
		{
			pSequence->Push(nextVert);
			return DFS(callback, pSequence, aUsed);
		}
	}
	pSequence->Pop();
	return DFS(callback, pSequence, aUsed);
}

BYTE* GraphBase::GetDistMap(BYTE initVert)
{
	BYTE* aDist = (BYTE*)malloc(m_vertices);
	FillMemory(aDist, m_vertices, -1);
	std::queue<BYTE>q;								// TODO: replace
	q.push(initVert);
	aDist[initVert] = 0;
	while (!q.empty())
	{
		BYTE vert = q.front();
		q.pop();
		for (BYTE nextv = 0; nextv < m_vertices; nextv++)
		{
			if (adjMat[vert][nextv] && aDist[nextv] == 255)
			{
				aDist[nextv] = aDist[vert] + 1;
				q.push(nextv);
			}
		}
	}
	return aDist;
}

BYTE GraphBase::GetVerticesCount()
{
	return m_vertices;
}