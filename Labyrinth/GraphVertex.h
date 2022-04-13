#pragma once
#include "RoundButton.h"
#include "List.h"

#define VERTEX_TYPE_ENTRANCE 1
#define VERTEX_TYPE_ROOM 2
#define VERTEX_TYPE_EXIT 3
#define VERTEX_TYPE_BINDING 4

class GraphVertex : public RoundButton
{
public:
	GraphVertex(int index, int x, int y);
	~GraphVertex();
public:
	float GetTrapChance();
	void SetTrapChance();
	int GetIndex();
	void SetType(BYTE type);
	BYTE GetType();

private:
	int m_index;		// vertex index in graph matrix
	float m_fTrapChance = 0;
	BYTE m_bType;		// entrance/exit/room vertex type
	bool m_bHasTrap;	// true if edge contains trap
};

