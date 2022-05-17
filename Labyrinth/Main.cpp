#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "Shlwapi.lib")
#include <iostream>
#include "File.h"
#include "Editor.h"
#include "Labyrinth.h" //d
#include "Queue.h"

Labyrinth* labyrinth;

int main()
{
    Queue<int> q(4);
    q.Pop();
    std::cout << "Do you want to open maze from file?(y/n)\n";
    char ch = 0;
    std::cin >> ch;
    if (ch == 'y')
    {
        labyrinth = LoadFromFile((WCHAR*)L"C:\\Users\\nullptr\\Desktop\\graph.maze");
        goto Edit;
    }
    std::cout << "Enter number of vertices (4-45)\n";
    short nVerts;
    std::cin >> nVerts;
    labyrinth = new Labyrinth(nVerts);
Edit:
    system("cls");
    ShowEditor(labyrinth);
    std::cout << "1. Path to the closest exit:\n";
    auto path = labyrinth->GetClosestVertPath();
    for (int i = 0; i < path.Size(); i++)
    {
        std::cout << (int)path[i];
        if (i != path.Size() - 1)
            std::cout << " => ";
    }
}
