#pragma once
#include "Labyrinth.h"
#include "GraphVertex.h"
#include "Graph.h"
#include "Direct3D.h"

#include <stdio.h>	 // swprintf_s
#include <shlwapi.h> // StrCatW

extern List<GraphVertex*> vertices;

extern GraphVertex* bindingVertex;
extern GraphVertex* translatingVertex;
extern GraphVertex* trapVertex;
extern BYTE oldType;
extern bool bBindingFlag;
extern bool bTranslatingFlag;
extern bool bTrapFlag;


void DrawTread();				// Main drawing routine
void ExitThreads();				// Stops both threads


void InitVertices(Graph* graph);	// Draw n vertices on screen, save list of vertices as GraphVertex class
void Update();

int GetHoverVertex();			// Return index of vertex being hovered on
void Bind(Graph* graph, GraphVertex* pVertex);
