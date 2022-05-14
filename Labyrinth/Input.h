#pragma once
#include "GraphBase.h"
#include "GraphVertex.h"
#include "Editor.h"

extern GraphVertex* bindingVertex;
extern GraphVertex* translatingVertex;
extern GraphVertex* editVertex;
extern EDGE editEdge;
extern BYTE oldType;
extern bool bBindingFlag;
extern bool bTranslatingFlag;
extern bool bTrapFlag;

void ProcessInput(WPARAM wParam);
void OnRMBDown();
void OnLMBDown();
void OnLMBUp();
