#pragma once
#include "Labyrinth.h"
#include "List.h"
#include "MainWindow.h" 
#include "GraphVertex.h"
#include "Graph.h"
#include "Direct3D.h"

#include <stdio.h> //for swprintf_s


void DrawTread();				// Main drawing routine
void KeyThread();				// Key state checking routine
void ExitThreads();				// Stops both threads


void InitVertices(Graph* graph);	// Draw n vertices on screen, save list of vertices as GraphVertex class
void Update();

int GetHoverVertex();			// Return index of vertex being hovered on
void Bind(Graph* graph, GraphVertex* pVertex);
