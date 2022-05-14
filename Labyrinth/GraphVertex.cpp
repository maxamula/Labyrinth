#include "GraphVertex.h"

GraphVertex::GraphVertex(int index, int x, int y)
{
	m_index = index;
	this->SetLocation(x, y);
	m_type = VERTEX_TYPE_NORMAL;
}

GraphVertex::~GraphVertex()
{

}

void GraphVertex::SetType(BYTE type)
{
	if (type > 0 && type < 5)
		m_type = type;
}

BYTE GraphVertex::GetType()
{
	return m_type;
}

int GraphVertex::GetIndex()
{
	return m_index;
}