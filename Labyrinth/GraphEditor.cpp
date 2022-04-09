#include "GraphEditor.h"
#include <iostream>


//Global 
List<GraphVertex*> vertices;

GraphVertex* bindingVertex;
BYTE oldType;
bool bBindingFlag = false;  // If false: OnKeyPressed set binding vertex, if true: bind vertex with bindingVertex

bool bDrawThread = true;	// Flag to stop thread
bool bKeyThread = true;


void DrawThread()
{
	InitD3D(hWnd);
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	d3ddev->BeginScene();
	InitVertices(graph);
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);

	while (bDrawThread)
	{
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
		d3ddev->BeginScene();
		Update();
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
		//Sleep(100);
	}
	bDrawThread = true;
}

void KeyThread()
{
	while (bKeyThread)
	{
		if (GetForegroundWindow() == hWnd)
		{
			if (GetAsyncKeyState(0x42)) // Bind key
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
									Bind(graph ,vertices[i]);					// Bind vertices
									bindingVertex->SetType(oldType);
									bBindingFlag = !bBindingFlag;
								}	
							}
						}
					}
				}
			}
			


			if (GetAsyncKeyState(0x41))	// Set exit Key
			{
				int vertIndex = GetHoverVertex();
				if (vertIndex != -1)
				{
					for (int i = 0; i < vertices.size(); i++)	// Find right vertex by it`s index
					{
						if (vertices[i]->GetIndex() == vertIndex)
						{
							// Todo: recalculate buttons table
							// add exit matrix
							// recalculate exit matrix
							vertices[i]->SetType(VERTEX_TYPE_EXIT);
						}
					}
				}
			}

			if (GetAsyncKeyState(0x53))	// Set room Key
			{
				int vertIndex = GetHoverVertex();
				if (vertIndex != -1)
				{
					for (int i = 0; i < vertices.size(); i++)	// Find right vertex by it`s index
					{
						if (vertices[i]->GetIndex() == vertIndex)
						{
							// Todo: recalculate buttons table
							//	remove exit vertex from exit matrix
							vertices[i]->SetType(VERTEX_TYPE_ROOM);
						}
					}
				}
			}

			if (GetAsyncKeyState(0x44))	// Set Entrance Key
			{
				int vertIndex = GetHoverVertex();
				if (vertIndex != -1)
				{
					for (int i = 0; i < vertices.size(); i++)	// Find right vertex by it`s index
					{
						if (vertices[i]->GetIndex() == vertIndex)
						{
							// Todo: recalculate buttons table
							// remove exit vertex from exit matrix 
							// recalculate entrance matrix
							vertices[i]->SetType(VERTEX_TYPE_ENTRANCE);
						}
					}
				}
			}

		}
		Sleep(150);
	}	
	bKeyThread = true;
}

void Update()
{
	LPD3DXFONT pFont = 0;
	D3DXCreateFont(d3ddev, 18, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &pFont);

	for (int v = 0; v < vertices.size(); v++)
	{
		D3DCOLOR color;
		switch (vertices[v]->GetType())
		{
		case VERTEX_TYPE_BINDING:
			color = D3DCOLOR_XRGB(255, 255, 0);
			break;
		case VERTEX_TYPE_ROOM:
			color = D3DCOLOR_XRGB(0, 0, 0);
			break;
		case VERTEX_TYPE_ENTRANCE:
			color = D3DCOLOR_XRGB(0, 255, 0);
			break;
		case VERTEX_TYPE_EXIT:
			color = D3DCOLOR_XRGB(255, 0, 0);
			break;
		default:
			break;
		} 


		for (int i = 0; i < graph->GetVerticesCount(); i++)
		{
			for (int j = 0; j < graph->GetVerticesCount(); j++)
			{
				if (graph->adjMatrix[i][j])
				{ 
					DrawLine(vertices[i]->GetLocation().x, vertices[i]->GetLocation().y, vertices[j]->GetLocation().x, vertices[j]->GetLocation().y);	// Draw line for each edge
				}
			}
		}


		VERTEX verts[16 + 1];

		for (int i = 0; i < 16 + 1; i++)
		{
			verts[i].x = vertices[v]->GetLocation().x + 20 * cos(3.14 * (i / (16 / 2.0f)));
			verts[i].y = vertices[v]->GetLocation().y + 20 * sin(3.14 * (i / (16 / 2.0f)));
			verts[i].z = 0;
			verts[i].rhw = 1;
			verts[i].color = color;
		}
		d3ddev->SetFVF(VERTEX::FVF);
		d3ddev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 16, &verts, sizeof(VERTEX));

		RECT rect{ 0, 0, vertices[v]->GetLocation().x + 10, vertices[v]->GetLocation().y + 10 };
		WCHAR szIndex[3];
		swprintf_s(szIndex, L"%d", vertices[v]->GetIndex());
		pFont->DrawTextW(NULL, szIndex, 2, &rect, DT_BOTTOM | DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));
	}

	pFont->Release();
}

void InitVertices(Graph* graph)
{
	LPD3DXFONT pFont = 0;
	D3DXCreateFont(d3ddev, 18, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &pFont);

	int count = graph->GetVerticesCount(); // number of vertices in graph
	
	int vertIndex = 0;						// vertex index;
	int x;									// Location to draw
	int y;									//
	int lineOffset = 360 / (count / 4);		// Offset betwen vertices
	if (count <= 32)
	{
		x = 400;
		y = 100;
	}
	else
	{
		x = 640 - (45 * (count / 4)) / 2;
		y = 360 - (45 * (count / 4)) / 2;
	}

	for (int v = 0; v < count; v++)
	{

		VERTEX verts[16 + 1];

		for (int i = 0; i < 16 + 1; i++)
		{
			verts[i].x = x + 20 * cos(3.14 * (i / (16 / 2.0f)));
			verts[i].y = y + 20 * sin(3.14 * (i / (16 / 2.0f)));
			verts[i].z = 0;
			verts[i].rhw = 1;
			verts[i].color = D3DCOLOR_XRGB(0, 0, 0);
		}
		d3ddev->SetFVF(VERTEX::FVF);
		d3ddev->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 16, &verts, sizeof(VERTEX));

		GraphVertex* gVert = new GraphVertex(vertIndex, x, y);
		vertices.addLast(gVert);				// Save vertex
		vertIndex++;							// Increase vertex index by 1

		RECT rect{ 0, 0, x + 10, y + 10 };
		pFont->DrawTextW(NULL, L"10", 2, &rect, DT_BOTTOM | DT_RIGHT, D3DCOLOR_XRGB(255, 255, 255));
		if (count <= 32)
		{
			if (v < 0.25f * count)
				x += lineOffset;
			else if (v < 0.5f * count)
				y += lineOffset;
			else if (v < 0.75 * count)
				x -= lineOffset;
			else if (v <= count)
				y -= lineOffset;
		}
		else
		{
			if (v < 0.25f * count)
				x += 45;
			else if (v < 0.5f * count)
				y += 45;
			else if (v < 0.75 * count)
				x -= 45;
			else if (v <= count)
				y -= 45;
		}
	}
	pFont->Release(); //free memory
}

int GetHoverVertex()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i]->CheckHover(hWnd))
			return i;
	}
	return -1;
}

void Bind(Graph* graph, GraphVertex* pVertex)
{
	graph->adjMatrix[bindingVertex->GetIndex()][pVertex->GetIndex()] = true;
}