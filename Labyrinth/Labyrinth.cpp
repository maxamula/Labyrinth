#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <iostream>
#include <random>
#include "Labyrinth.h"
#include "MainWindow.h"


// Global vars 
Graph* graph = new Graph(50);

int g_vertices;
Table<int, List<int>> buttons;



int main()
{
	std::cout << "Enter number of graph vertices" << std::endl;
	int vertices;
	std::cin >> vertices;
	WinMain(0, 0, 0, 0);
	
}

bool Labyrinth::SetVertices(int vertices, int entrances)
{
	if (entrances > vertices)
		return false;
	m_entrances = entrances;
	m_vertices = vertices;
	std::random_device rd;
	std::uniform_int_distribution<int> rndVert(0, vertices);
	std::uniform_int_distribution<int> distr(15, 25);
	/*for (int entr = 0; entr < m_entrances; entr++)
	{
		List<int> btn;
		for()
	}*/
}