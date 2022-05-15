#include "File.h"

bool bLoadFromFile = false;
POINT* aPos = NULL;

struct MAZE_HEADER {
	BYTE verts;
	BYTE entr;
	BYTE nExits;
};

Labyrinth* LoadFromFile(WCHAR* szPath)
{
	std::fstream input(szPath, std::ios::in | std::ios::binary);
	input.seekg(0, input.end);
	int nFileSize = input.tellg();
	if (nFileSize == -1)
	{
		std::cout << "Couldn't open the file" << std::endl;
		system("pause");
		exit(1);
	}
	bLoadFromFile = true;
	input.seekg(0, input.beg);
	char* file = (char*)malloc(nFileSize);
	input.read(file, nFileSize);
	int offset = 0;
	MAZE_HEADER* pHeader = (MAZE_HEADER*)file;
	BYTE verts = pHeader->verts;
	offset += sizeof(MAZE_HEADER);
	Labyrinth* lab = new Labyrinth(verts);
	lab->entrance = pHeader->entr;
	for (int i = 0; i < pHeader->nExits; i++)
	{
		BYTE val;
		memcpy(&val, file + offset, 1);
		lab->exits.AddLast(val);
		offset++;
	}
	for (BYTE i = 0; i < verts; i++)
	{
		for (BYTE j = 0; j < verts; j++)
		{
			bool val;
			memcpy(&val, file+offset, 1);
			offset++;
			lab->adjMat[i][j] = val;
		}
	}
	for (BYTE i = 0; i < verts; i++)
	{
		for (BYTE j = 0; j < verts; j++)
		{
			EDGE edge{ i, j };
			BYTE val;
			memcpy(&val, file + offset, 1);
			lab->traps.Put(edge, val);
			offset++;
		}
	}
	for (BYTE i = 0; i < verts; i++)
	{
		for (BYTE j = 0; j < verts; j++)
		{
			EDGE edge{ i, j };
			BYTE val;
			memcpy(&val, file + offset, 1);
			lab->time.Put(edge, val);
			offset++;
		}
	}
	aPos = (POINT*)malloc(verts*sizeof(POINT));
	memcpy(aPos, file + offset, verts * sizeof(POINT));
	return lab;
}

void SaveToFile(Labyrinth* lab, WCHAR* szPath)
{
	int offset = 0;
	BYTE verts = lab->GetVerticesCount();
	char* buf = (char*)malloc(sizeof(MAZE_HEADER) + lab->exits.Size() + pow(verts, 2) + pow(verts, 2) + pow(verts, 2) + verts * sizeof(POINT));
	MAZE_HEADER header{verts, lab->entrance, lab->exits.Size()};
	memcpy(buf, &header, sizeof(header));
	offset += sizeof(header);
	for (int i = 0; i < lab->exits.Size(); i++)
	{
		BYTE val = lab->exits[i];
		memcpy(buf+offset, &val, 1);
		offset++;
	}
	for (int i = 0; i < verts; i++)
	{
		for (int j = 0; j < verts; j++)
		{
			bool val = lab->adjMat[i][j];
			memcpy(buf + offset, &val, 1);
			offset++;
		}
	}
	for (BYTE i = 0; i < verts; i++) 
	{
		for (BYTE j = 0; j < verts; j++)
		{
			BYTE val = lab->traps.Get(EDGE{i, j});
			memcpy(buf + offset, &val, 1);
			offset++;
		}
	}
	for (BYTE i = 0; i < verts; i++)
	{
		for (BYTE j = 0; j < verts; j++)
		{
			BYTE val = lab->time.Get(EDGE{ i, j });
			memcpy(buf + offset, &val, 1);
			offset++;
		}
	}
	for (int i = 0; i < verts; i++)
	{
		POINT pos = vertices[i]->GetLocation();
		memcpy(buf + offset, &pos, sizeof(POINT));
		offset += sizeof(POINT);
	}
	std::fstream output(szPath, std::ios::out | std::ios::binary);
	output.write(buf, offset);
	output.close();
	free(buf);
}