#pragma once
#include "List.h"
#include "Stack.h"
#include <queue>		//d
#include <windows.h>

typedef List<BYTE> Path_t;

class GraphBase
{
public:
	GraphBase(BYTE verts);
	~GraphBase();
public:
	bool** adjMat;

	void DFS(bool (*callback)(BYTE vert), Stack<BYTE>* pSequence, bool* aUsed);		// Calls callback for each vert
	BYTE* GetDistMap(BYTE initVert);												// Returns distance array from initial to other
	BYTE GetVerticesCount();
private:
	BYTE m_vertices;
};

struct EDGE {
	BYTE v1;
	BYTE v2;
};