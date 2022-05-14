#pragma once
#include "Direct3D.h"
#include "MainWindow.h"
#include "GraphBase.h"
#include "GraphVertex.h"
#include "Labyrinth.h"
#include "Menu.h"
#include "Input.h"
#include "File.h"

#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

extern Labyrinth* graph;
extern List<GraphVertex*> vertices;

void ShowEditor(Labyrinth* lab);

void DrawThread();				// Main drawing routine
void ExitThread();				// Stop thread

void LoadVertices();			// load verts coords from file
void InitVertices();			// Draw n vertices on screen, save list of GraphVertex classes
void Update();

BYTE GetHoverVertex();			// Return index of vertex being hovered on
//void Bind(Graph* graph, GraphVertex* pVertex);
