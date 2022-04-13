#include "MainWindow.h"
#include "RoundButton.h"
#include <iostream>


void DrawThread();
LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE hInstance;
HINSTANCE hPrevInst;
LPSTR lpszArgs;
int nWinMode;
HWND hWnd;

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
    MSG msg;
    WNDCLASS wc;

    ZeroMemory(&wc, sizeof(wc));
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Editor";
    wc.lpfnWndProc = WindowFunc;
    wc.style = 0;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, L"An error occured", L"Error", MB_OK);
        return 1;
    }
    
    hWnd = CreateWindow(L"Editor", L"Edit Graph", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, HWND_DESKTOP, NULL, hInstance, NULL);
    ShowWindow(hWnd, SW_SHOWNORMAL);
    
   
    CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DrawThread, 0, 0, 0));


    while (GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
    }   
    ExitThreads();
    d3ddev->Release();
    d3d->Release();
    return 0;
}


LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
    switch (message) {
    case WM_KEYDOWN:

		if (wParam == 0x42) // Bind key
		{
			int vertIndex = GetHoverVertex();
			if (vertIndex != -1)
			{
				if (!bBindingFlag)
				{
					for (int i = 0; i < vertices.size(); i++)	// Find right vertex by it`s index
					{
						if (vertices[i]->GetIndex() == vertIndex)
						{
							oldType = vertices[i]->GetType();				// save old vertex type
							vertices[i]->SetType(VERTEX_TYPE_BINDING);		// Set vertex type
							bindingVertex = vertices[i];					// Set binding vertex
							bBindingFlag = !bBindingFlag;					// Change binding flag
						}
					}
				}
				else
				{
					for (int i = 0; i < vertices.size(); i++)	// Find right vertex by it`s index
					{
						if (vertices[i]->GetIndex() == vertIndex)
						{
							if (vertices[i] == bindingVertex)		// If vertex chosen twice: change vertex type to old, change flag back
							{
								vertices[i]->SetType(oldType);
								bBindingFlag = !bBindingFlag;
							}
							else
							{
								Bind(graph, vertices[i]);					// Bind vertices
								bindingVertex->SetType(oldType);
								bBindingFlag = !bBindingFlag;
							}
						}
					}
				}
			}
		}



		if (wParam == 0x41)	// Set exit Key
		{
			int vertIndex = GetHoverVertex();
			if (vertIndex != -1)
			{
				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices[i]->GetIndex() == vertIndex)
					{
						if (vertices[i]->GetType() != VERTEX_TYPE_EXIT)
						{
							graph->exits.addLast(vertIndex);
							vertices[i]->SetType(VERTEX_TYPE_EXIT);
						}
					}
				}
			}
		}

		if (wParam == 0x53)	// Set room Key
		{
			int vertIndex = GetHoverVertex();
			if (vertIndex != -1)
			{
				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices[i]->GetIndex() == vertIndex)
					{
						graph->exits.Remove(vertIndex);
						vertices[i]->SetType(VERTEX_TYPE_ROOM);
					}
				}
			}
		}

		if (wParam == 0x44)	// Set Entrance Key
		{
			int vertIndex = GetHoverVertex();
			if (vertIndex != -1)
			{
				for (int i = 0; i < vertices.size(); i++)
				{
					if (vertices[i]->GetIndex() == vertIndex)
					{
						for (int j = 0; j < vertices.size(); j++)
						{
							if (vertices[j]->GetType() == VERTEX_TYPE_ENTRANCE)
							{
								vertices[j]->SetType(VERTEX_TYPE_ROOM);
								break;
							}
						}
						graph->exits.Remove(vertIndex);
						graph->entrance = vertIndex;
						vertices[i]->SetType(VERTEX_TYPE_ENTRANCE);
					}
				}
			}
		}

		if (wParam == 0x58) // Set trap key
		{
			int vertIndex = GetHoverVertex();
			if (vertIndex != -1)
			{
				if (!bTrapFlag)
				{
					for (int i = 0; i < vertices.size(); i++)
					{
						if (vertices[i]->GetIndex() == vertIndex)
						{
							oldType = vertices[i]->GetType();
							vertices[i]->SetType(VERTEX_TYPE_BINDING);
							trapVertex = vertices[i];
							bTrapFlag = !bTrapFlag;	
						}
					}
				}
				else
				{
					for (int i = 0; i < vertices.size(); i++)
					{
						if (vertices[i]->GetIndex() == vertIndex)
						{
							if (vertices[i] == bindingVertex)
							{
								vertices[i]->SetType(oldType);
								bTrapFlag = !bTrapFlag;
							}
							else
							{
								std::cout << "Enter the value:" << std::endl;
								int chance = 0;
								std::cin >> chance;
								graph->trapMatrix[trapVertex->GetIndex()][i] = chance;
								trapVertex->SetType(oldType);
								bTrapFlag = !bTrapFlag;
							}
						}
					}
				}
			}
		}
        break;
	case WM_LBUTTONDOWN:
		if (GetHoverVertex() != -1)
		{
			if (!bTranslatingFlag)
			{
				translatingVertex = vertices[GetHoverVertex()];
				bTranslatingFlag = true;
			}
		}
		break;
	case WM_LBUTTONUP:
		bTranslatingFlag = false;
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}