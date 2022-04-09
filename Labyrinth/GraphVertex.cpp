#include "GraphVertex.h"


GraphVertex::GraphVertex(int index, int x, int y)
{
	m_index = index;
	this->SetLocation(x, y);
	m_bType = VERTEX_TYPE_ROOM;
}

GraphVertex::~GraphVertex()
{

}

void GraphVertex::SetType(BYTE type)
{
	if(type > 0 && type < 5)
		m_bType = type;
}

BYTE GraphVertex::GetType()
{
	return m_bType;
}

int GraphVertex::GetIndex()
{
	return m_index;
}
