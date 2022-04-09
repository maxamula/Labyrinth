#pragma once
#include <math.h>
#include <windows.h>
class RoundButton
{
public:
	bool CheckHover(HWND hWnd);
	POINT GetLocation();
	void SetLocation(int x, int y);
private:
	int x, y; // Location
	int rad = 20; // Radius
};

