#include "File.h"

struct MAZE_HEADER
{
	int verts;
	int entrance;

	int exSize;
	int exCapacity;
};


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

	// Graph::exits
	memcpy((void*)((long long int)graph + 0x18), &pHeader->exSize, sizeof(int));		// set list size
	memcpy((void*)((long long int)graph + 0x1c), &pHeader->exCapacity, sizeof(int));	// set list capacity

	char* pData = (char*)malloc(pHeader->exCapacity * sizeof(int));						// allocate memory 
	memcpy(pData, (void*)(file + sizeof(MAZE_HEADER)), pHeader->exSize * sizeof(int));	// copy exits list to a new memory cave
	memcpy((void*)((long long int)graph + 0x20), &pData, sizeof(char*));				// set pointer to data

	// Graph::agjMatrix

	// Graph::TrapMatrix

	free(file);
	input.close();
	return graph;
}

void SaveToFile(Graph* graph, WCHAR* szPath)
{
	int offset = 0;
	char* buf = (char*)malloc(100000);
	int v = graph->GetVerticesCount();
	memcpy(buf, &v, 4);
	offset += 4;
	memcpy(buf + offset, &graph->entrance, 4);
	offset += 4;
	int e = graph->exits.size();
	memcpy(buf + offset, &e, 4);
	offset += 4;
	int cp = graph->exits.cap();
	memcpy(buf+ offset, &cp, 4);         // offset to capacity
	offset += 4;
	memcpy(buf+offset, graph->exits.data(), graph->exits.size()*4);
	offset += graph->exits.size()*4;
	std::fstream output(szPath, std::ios::out | std::ios::binary);
	output.write(buf, offset+1);
	output.close();
}