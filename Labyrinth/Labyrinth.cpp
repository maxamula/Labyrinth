#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <iostream>
#include <random>
#include "Labyrinth.h"
#include "MainWindow.h"


void Help();

// Global vars 
Graph* graph;

int g_vertices;
Table<int, List<int>> buttons;



int main()
{
	VerticesInput:
	std::cout << "Enter number of graph vertices" << std::endl;
	int iVertices;
	std::cin >> iVertices;
	if (iVertices >= 4 && iVertices <= 45)
		graph = new Graph(iVertices);
	else
	{
		std::cout << "Number must be betwen 4 and 55" << std::endl;
		goto VerticesInput;
	}	
	system("cls");
	Help();
	WinMain(0, 0, 0, 0);
	graph->exits.Sort();
	for (int i = 0; i < graph->exits.size(); i++)
	{
		std::cout << graph->exits[i] << std::endl;
	}
}

void Help()
{
	std::cout << "\"b\" - bind vertices" << std::endl;
	std::cout << "\"a\" - set vertex as exit" << std::endl;
	std::cout << "\"s\" - set vertex as normal" << std::endl;
	std::cout << "\"d\" - set vertex as entrance" << std::endl;
	std::cout << "\"q\" - translate vertex" << std::endl;
}