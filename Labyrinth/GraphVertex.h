#pragma once
#include "RoundButton.h"

#define VERTEX_TYPE_ENTRANCE 1
#define VERTEX_TYPE_NORMAL 2
#define VERTEX_TYPE_EXIT 3
#define VERTEX_TYPE_HILIGHTED 4

class GraphVertex : public RoundButton
{
public:
	GraphVertex(int index, int x, int y);
	~GraphVertex();
public:
	int GetIndex();
	void SetType(BYTE type);
	BYTE GetType();

private:
	int m_index;		// vertex index in graph matrix
	BYTE m_type;		// entrance/exit/room vertex type
};

