#include "MainWindow.h"
#include <windowsx.h>

LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND hWnd;

int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszArgs, int nWinMode)
{
	MSG msg;
	WNDCLASS wc;

	ZeroMemory(&wc, sizeof(wc));
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Editor";
	wc.lpfnWndProc = WindowFunc;
	wc.style = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockBrush(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, L"An error occured", L"Error", MB_OK);
		return 1;
	}

	hWnd = CreateWindow(L"Editor", L"Edit Graph", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 100, 100, 1280, 720, HWND_DESKTOP, NULL, hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);

	CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DrawThread, 0, 0 ,0));
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


LRESULT CALLBACK WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//pass params to imgui handler
	if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
		return true;


	switch (message) {
	case WM_KEYDOWN:
		ProcessInput(wParam);
		break;
	case WM_RBUTTONDOWN:
		OnRMBDown();
		break;
	case WM_LBUTTONDOWN:
		OnLMBDown();
		break;
	case WM_LBUTTONUP:
		OnLMBUp();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}