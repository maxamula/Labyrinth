#include "Editor.h"
#include <chrono>		//d
#include <iostream>		//d


//Global varriables
Labyrinth* graph = NULL;
List<GraphVertex*> vertices;

bool bDraw = true;



void ShowEditor(Labyrinth* lab)
{
	graph = lab;
	WinMain(0, 0, 0, 0);
	bDraw = false;
	while(!bDraw) {}
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
	ReleaseD3D();
}

void DrawThread()
{
	InitD3D(hWnd);
	//Init Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(d3ddev);
	ImGui::StyleColorsLight();
	//Init Verts position
	bLoadFromFile ? LoadVertices() : InitVertices();
	while (bDraw)
	{
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
		d3ddev->BeginScene();
		Update();
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}	
	bDraw = true;
}

void InitVertices()
{
	int count = graph->GetVerticesCount(); // number of vertices in graph

	int vertIndex = 0;						// vertex index;
	int x;									// Location to draw
	int y;									//
	int lineOffset = 360 / (count / 4);		// Offset betwen vertices

	x = 640 - (45 * (count / 4));
	y = (45 * (count / 4));

	for (int v = 0; v < count; v++)
	{
		GraphVertex* gVert = new GraphVertex(vertIndex, x, y);

		for (int i = 0; i < graph->exits.Size(); i++)
		{
			if (vertIndex == graph->exits[i])
				gVert->SetType(VERTEX_TYPE_EXIT);
		}
		if (vertIndex == graph->entrance)
			gVert->SetType(VERTEX_TYPE_ENTRANCE);
		vertices.AddLast(gVert);				// Save vertex
		vertIndex++;							// Increase vertex index by 1

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
}

void LoadVertices()
{
	int count = graph->GetVerticesCount();
	int vertIndex = 0;

	for (BYTE v = 0; v < count; v++)
	{
		GraphVertex* gVert = new GraphVertex(vertIndex, aPos[vertIndex].x, aPos[vertIndex].y);

		for (BYTE i = 0; i < graph->exits.Size(); i++)
		{
			if (vertIndex == graph->exits[i])
				gVert->SetType(VERTEX_TYPE_EXIT);
		}
		if (vertIndex == graph->entrance)
			gVert->SetType(VERTEX_TYPE_ENTRANCE);
		vertices.AddLast(gVert);
		vertIndex++;
	}
}

void Update()
{
	LPD3DXFONT pFont = 0;
	D3DXCreateFont(d3ddev, 18, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &pFont);

	if (bTranslatingFlag)
	{
		POINT pos;
		GetCursorPos(&pos);
		ScreenToClient(hWnd, &pos);
		translatingVertex->SetLocation(pos.x, pos.y);
	}

	for (int v = 0; v < vertices.Size(); v++)
	{
		D3DCOLOR color;
		switch (vertices[v]->GetType())
		{
		case VERTEX_TYPE_HILIGHTED:
			color = D3DCOLOR_XRGB(255, 255, 0);
			break;
		case VERTEX_TYPE_NORMAL:
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


		for (BYTE i = 0; i < graph->GetVerticesCount(); i++)
		{
			for (BYTE j = 0; j < graph->GetVerticesCount(); j++)
			{
				if (graph->adjMat[i][j])
				{
					POINT vec{ vertices[j]->GetLocation().x - vertices[i]->GetLocation().x , vertices[j]->GetLocation().y - vertices[i]->GetLocation().y };

					//Display edge trap chance
					if (graph->traps.Get(EDGE{ i, j }) != 0)
					{
						RECT chanceRect{ 0, 0, vertices[j]->GetLocation().x - vec.x / 2, vertices[j]->GetLocation().y - vec.y / 2 };
						WCHAR szChance[5];
						swprintf_s(szChance, L"%d", graph->traps.Get(EDGE{ i, j }));
						WCHAR* str = StrCatW(szChance, L"%");
						pFont->DrawTextW(NULL, szChance, wcslen(szChance), &chanceRect, DT_BOTTOM | DT_RIGHT, D3DCOLOR_XRGB(0, 0, 255));
					}

					if (graph->time.Get(EDGE{ i, j }) != 0)
					{
						RECT chanceRect{ 0, 0, vertices[j]->GetLocation().x - vec.x / 3, vertices[j]->GetLocation().y - vec.y / 3 };
						WCHAR szTime[5];
						swprintf_s(szTime, L"%d", graph->time.Get(EDGE{ i, j }));
						pFont->DrawTextW(NULL, szTime, wcslen(szTime), &chanceRect, DT_BOTTOM | DT_RIGHT, D3DCOLOR_XRGB(255, 0, 0));
					}

					// Draw edges
					float a = SetLength(vec.x, vec.y, 20);
					vec.x = vec.x * a;
					vec.y = vec.y * a;
					POINT vec2{ vertices[i]->GetLocation().x - vertices[j]->GetLocation().x , vertices[i]->GetLocation().y - vertices[j]->GetLocation().y };
					vec2.x = vec2.x * a;
					vec2.y = vec2.y * a;
					DrawArrow(vertices[i]->GetLocation().x - vec2.x, vertices[i]->GetLocation().y - vec2.y, vertices[j]->GetLocation().x - vec.x, vertices[j]->GetLocation().y - vec.y);
					DrawLine(vertices[i]->GetLocation().x - vec2.x, vertices[i]->GetLocation().y - vec2.y, vertices[j]->GetLocation().x - vec.x, vertices[j]->GetLocation().y - vec.y);	// Draw line for each edge
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
	if (bDrawMenu)
	{
		DrawMenu(graph);
	}
}

BYTE GetHoverVertex()
{
	for (BYTE i = 0; i < vertices.Size(); i++)
	{
		if (vertices[i]->CheckHover(hWnd))
			return i;
	}
	return 255;
}