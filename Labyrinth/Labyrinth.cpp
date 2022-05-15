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