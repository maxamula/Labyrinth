#include "Labyrinth.h"

Labyrinth::Labyrinth(BYTE verts) : GraphBase(verts)
{
	for (BYTE i = 0; i < this->GetVerticesCount(); i++)
	{
		for (BYTE j = 0; j < this->GetVerticesCount(); j++)
		{
			this->traps.Put(EDGE{i, j}, 0);
		}
	}

	for (BYTE i = 0; i < this->GetVerticesCount(); i++)
	{
		for (BYTE j = 0; j < this->GetVerticesCount(); j++)
		{
			this->time.Put(EDGE{ i, j }, 0);
		}
	}
}

Labyrinth::~Labyrinth()
{

}

Path Labyrinth::GetClosestVertPath()
{
	Path path; //retn val

	BYTE* aDist = this->GetDistMap(entrance);
	BYTE minDist = exits[0];
	for (int exit = 0; exit < exits.Size(); exit++)
	{
		if (aDist[exits[exit]] < aDist[minDist])
			minDist = exits[exit];
	}
	// BFS
	Queue<BYTE>** aPath = (Queue<BYTE>**)malloc(GetVerticesCount()*sizeof(Queue<BYTE>*));
	ZeroMemory(aPath, GetVerticesCount() * sizeof(std::queue<BYTE>*));
	bool* aUsed = (bool*)malloc(GetVerticesCount());
	ZeroMemory(aUsed, GetVerticesCount());
	Queue<BYTE>q;
	q.Push(entrance);
	aUsed[entrance] = true;
	Queue<BYTE>* p = new Queue<BYTE>();
	p->Push(entrance);
	aPath[entrance] = p;
	while (!q.Empty())
	{
		BYTE vert = q.Front();
		q.Pop();
		for (BYTE nextv = 0; nextv < GetVerticesCount(); nextv++)
		{
			if (adjMat[vert][nextv] && !aUsed[nextv] && vert != nextv)
			{
				Queue<BYTE>* nextp = new Queue<BYTE>();
				*nextp = *aPath[vert];
				nextp->Push(nextv);
				aPath[nextv] = nextp;
				if (nextv == minDist)
				{
					int times = nextp->Size();
					for (int t = 0; t < times; t++)
					{
						path.AddLast(nextp->Front());
						nextp->Pop();
					}
					goto Retn;
				}
				aUsed[nextv] = true;
				q.Push(nextv);
			}
		}
	}
	Retn:
	// free memory
	for (BYTE i = 0; i < GetVerticesCount(); i++)
	{
		delete aPath[i];
	}
	return path;
}