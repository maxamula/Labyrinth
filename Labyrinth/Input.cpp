#include "Input.h"

GraphVertex* bindingVertex;
GraphVertex* translatingVertex;
GraphVertex* editVertex;
EDGE editEdge;
BYTE oldType;
bool bBindingFlag;
bool bTranslatingFlag;
bool bTrapFlag;

void ProcessInput(WPARAM wParam)
{
	if (wParam == 0x41)	// Set exit Key
	{
		int vertIndex = GetHoverVertex();
		if (vertIndex != 255)
		{
			for (int i = 0; i < vertices.Size(); i++)
			{
				if (vertices[i]->GetIndex() == vertIndex)
				{
					if (vertices[i]->GetType() != VERTEX_TYPE_EXIT)
					{
						if (graph->entrance == vertIndex)
							graph->entrance = -1;
						graph->exits.AddLast(vertIndex);
						vertices[i]->SetType(VERTEX_TYPE_EXIT);
					}
				}
			}
		}
	}

	if (wParam == 0x53)	// Set room Key
	{
		int vertIndex = GetHoverVertex();
		if (vertIndex != 255)
		{
			for (int i = 0; i < vertices.Size(); i++)
			{
				if (vertices[i]->GetIndex() == vertIndex)
				{
					if (vertices[i]->GetType() == VERTEX_TYPE_ENTRANCE)
						graph->entrance = -1;
					graph->exits.Remove(vertIndex);
					vertices[i]->SetType(VERTEX_TYPE_NORMAL);
				}
			}
		}
	}

	if (wParam == 0x44)	// Set Entrance Key
	{
		int vertIndex = GetHoverVertex();
		if (vertIndex != -1)
		{
			for (int i = 0; i < vertices.Size(); i++)
			{
				if (vertices[i]->GetIndex() == vertIndex)
				{
					for (int j = 0; j < vertices.Size(); j++)
					{
						if (vertices[j]->GetType() == VERTEX_TYPE_ENTRANCE)
						{
							vertices[j]->SetType(VERTEX_TYPE_NORMAL);
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

	if (wParam == VK_F2)
	{
		SaveToFile(graph, (WCHAR*)L"C:\\Users\\nullptr\\Desktop\\graph.maze");
	}

	if (wParam == VK_F1)		// Open menu
	{
		bDrawMenu = !bDrawMenu;
	}
}

void OnRMBDown() 
{
	int vertIndex = GetHoverVertex();
		if (vertIndex != 255)
		{
			if (!bBindingFlag)
			{
				for (int i = 0; i < vertices.Size(); i++)	// Find right vertex by it`s index
				{
					if (vertices[i]->GetIndex() == vertIndex)
					{
						oldType = vertices[i]->GetType();				// save old vertex type
						vertices[i]->SetType(VERTEX_TYPE_HILIGHTED);	// Set vertex type
						bindingVertex = vertices[i];					// Set binding vertex
						bBindingFlag = !bBindingFlag;					// Change binding flag
					}
				}
			}
			else
			{
				for (int i = 0; i < vertices.Size(); i++)	// Find right vertex by it`s index
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
							graph->adjMat[bindingVertex->GetIndex()][i] = !graph->adjMat[bindingVertex->GetIndex()][i]; // Bind vertices
							bindingVertex->SetType(oldType);
							bBindingFlag = !bBindingFlag;
						}
					}
				}
			}
		}
}

void OnLMBDown()
{
	if (GetHoverVertex() != 255)
	{
		if (!bTranslatingFlag)
		{
			translatingVertex = vertices[GetHoverVertex()];
			bTranslatingFlag = true;
		}
	}
}

void OnLMBUp()
{
	bTranslatingFlag = false;
}