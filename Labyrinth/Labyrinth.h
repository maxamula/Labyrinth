#pragma once
#include "Graph.h"
#include "Table.h"

extern Graph* graph;

class Labyrinth
{
public:
	Labyrinth();
	~Labyrinth();
public:
	bool SetVertices(int vertices, int entrances);
private:
	int m_vertices;
	int m_entrances;
	Table<int, List<int>> m_buttons;

};

