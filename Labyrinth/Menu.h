#pragma once
#include "Labyrinth.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>


extern BYTE* pChance;
extern BYTE* pTime;
extern bool bDrawMenu;

void DrawMenu(Labyrinth* graph);

