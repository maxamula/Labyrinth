#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Shlwapi.lib")
#include <iostream>
#include <random>
#include "Table.h"
#include "Labyrinth.h"
#include "MainWindow.h"

#define MAX_FILE_PATH 260

void Help();
void CreateButtonTable();

// Global vars
Graph* graph;



int main()
{	
	
	std::cout << "Do you want open maze from file? (y/n)" << std::endl;
	if (getchar() == (int)'y')
	{
		std::cout << "Enter file path" << std::endl;
		WCHAR szFilePath[MAX_FILE_PATH];
		std::wcin >> szFilePath;
		//graph = LoadFromFile(szFilePath);
		graph = LoadFromFile((WCHAR*)L"C:\\Users\\nullptr\\Desktop\\graph.maze");
		goto Edit;
	}
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

Edit:
	system("cls");
	Help();
	WinMain(0, 0, 0, 0);
	system("cls");
	graph->exits.Sort();

	//SaveToFile(graph, (WCHAR*)L"C:\\Users\\nullptr\\Desktop\\graph.maze");
	if (graph->exits.size() == 0 || graph->entrance == -1)
	{
		std::cout << "Invalid input data" << std::endl;
		system("pause");
		exit(1);
	}
	
	
	system("pause");
}

void Help()
{
	std::cout << "\"b\" - bind vertices" << std::endl;
	std::cout << "\"a\" - set vertex as exit" << std::endl;
	std::cout << "\"s\" - set vertex as normal" << std::endl;
	std::cout << "\"d\" - set vertex as entrance" << std::endl;
	std::cout << "\"x\" - set trap chance" << std::endl;
}
