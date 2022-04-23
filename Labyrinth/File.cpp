#include "File.h"

#pragma pack(push, 1)																	// Disable structure padding
struct MAZE_HEADER
{
	unsigned char verts;					 											// Number of vertices
	char entrance;																		// Entrance vertex
};
#pragma pack(pop)

Graph* LoadFromFile(WCHAR* szFilePath)
{
	std::fstream input(szFilePath, std::ios::in | std::ios::binary);
	input.seekg(0, input.end);
	int nFileSize = input.tellg();
	if (nFileSize == -1)
	{
		std::cout << "Couldn't open the file" << std::endl;
		system("pause");
		exit(1);
	}
	input.seekg(0, input.beg);
	char* file = (char*)malloc(nFileSize);
	input.read(file, nFileSize);
	
	MAZE_HEADER* pHeader = (MAZE_HEADER*)file;
	Graph* graph = new Graph(pHeader->verts); 
	
	// Build graph structure from file	
	memcpy(&graph->entrance, &pHeader->entrance, sizeof(BYTE));

	// Graph::exits
	graph->exits = *(new List<BYTE>(file+sizeof(MAZE_HEADER)));

	// Graph::agjMatrix
	bool** adjMatrix = (bool**)malloc(pHeader->verts*sizeof(bool*));
	for (int i = 0; i < pHeader->verts; i++)
	{
		bool* pRow = (bool*)(file + sizeof(MAZE_HEADER) + *((int*)(file + sizeof(MAZE_HEADER))) + 4 + (i * pHeader->verts));		//2246411D9AC --- 2246411d9ac
		memcpy(&adjMatrix[i], &pRow, sizeof(bool*));
	}
	graph->adjMatrix = adjMatrix;

	// Graph::traps


	input.close();
	return graph;
}

void SaveToFile(Graph* graph, WCHAR* szPath)
{
	int offset = 0;
	char* buf = (char*)malloc(100000);

	// Header
	MAZE_HEADER header;
	header.verts = graph->GetVerticesCount();
	header.entrance = graph->entrance;
	memcpy(buf, &header, sizeof(MAZE_HEADER));
	offset += sizeof(MAZE_HEADER);

	// Exits list
	offset += graph->exits.CopyData(buf+offset);

	// AdjMatrix
	for (int i = 0; i < graph->GetVerticesCount(); i++)
	{
		memcpy(buf + offset, graph->adjMatrix[i], graph->GetVerticesCount());
		offset += graph->GetVerticesCount();
	}

	// Traps
	//graph->traps.CopyData(buf+offset, );

	std::fstream output(szPath, std::ios::out | std::ios::binary);
	output.write(buf, offset);
	output.close();
	free(buf);
}