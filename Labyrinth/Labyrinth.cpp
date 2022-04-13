#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Shlwapi.lib")
#include <iostream>
#include <random>
#include "Labyrinth.h"
#include "MainWindow.h"


void Help();

// Global vars 
Graph* graph;

int g_vertices;
Table<int, List<int>*> buttons;



int main()
{
	std::cout << sizeof(List<int>) << std::endl;
	std::cout << "Do you want open maze from file? (y/n)" << std::endl;
	int answer = getchar();
	if (answer == (int)'y')
	{
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
	SaveToFile(graph, (WCHAR*)L"C:\\Users\\nullptr\\Desktop\\graph.maze");
	if (graph->exits.size() == 0 || graph->entrance == -1)
	{
		std::cout << "Invalid input data" << std::endl;
		system("pause");
		exit(1);
	}
	//graph->exits.Sort();
	std::cout << "Enter number of buttons(2-7)" << std::endl;
	int nButtons;
	std::cin >> nButtons;
	for (int i = 0; i < nButtons; i++)
	{
		List<int>* exits = new List<int>();
		for (int j = 0; j < 2 + rand() % (int)round(0.5f * graph->exits.size()); j++)
		{
			exits->addLast(0 + rand() % graph->exits.size());
		}
		buttons.Put(1, exits);
	}
	system("cls");
	for (int i = 0; i < nButtons; i++)
	{
		std::cout << "Button " << i << ":";
		for (int j = 0; j < buttons.Get(i)->size(); j++)
		{
			std::cout << buttons.Get(i)->operator[](j) << " ";
		}
		std::cout << std::endl;
	}
}

void Help()
{
	std::cout << "\"b\" - bind vertices" << std::endl;
	std::cout << "\"a\" - set vertex as exit" << std::endl;
	std::cout << "\"s\" - set vertex as normal" << std::endl;
	std::cout << "\"d\" - set vertex as entrance" << std::endl;
	std::cout << "\"x\" - set trap chance" << std::endl;
}