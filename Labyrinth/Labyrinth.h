#pragma once
#include "GraphBase.h"
#include "HashMap.h"

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

	Path_t GetClosestPath();
	BYTE GetSurvivalChance(Path_t path);
	
private:
	Path_t GetMinDist(BYTE vert, BYTE* pMinDist);
};

