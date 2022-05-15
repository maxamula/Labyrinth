#pragma once
#include "Labyrinth.h"
#include "Editor.h"
#include <fstream>
#include <iostream>
#include <windows.h>

extern bool bLoadFromFile;
extern POINT* aPos;

Labyrinth* LoadFromFile(WCHAR* szPath);
void SaveToFile(Labyrinth* lab, WCHAR* szPath);

