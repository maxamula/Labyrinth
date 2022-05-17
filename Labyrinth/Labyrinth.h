#pragma once
#include "GraphBase.h"
#include "HashMap.h"
#include "Queue.h"

class Labyrinth : public GraphBase
{
public:
	Labyrinth(BYTE verts);
	~Labyrinth();
public:
	BYTE entrance = -1;
	List<BYTE> exits;
	HashMap<EDGE, BYTE> traps;
	HashMap<EDGE, BYTE> time;

	Path GetClosestVertPath();
	BYTE GetSurvivalChance(Path path);
	
private:
	Path GetMinDist(BYTE vert, BYTE* pMinDist);
};

