#pragma once
#include "Direct3D.h"
#include "Editor.h"
#include "Input.h"
#include <windows.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); // messages handler
extern HWND hWnd;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode);