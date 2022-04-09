#include "RoundButton.h"

bool RoundButton::CheckHover(HWND hWnd)
{
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(hWnd, &pos);
	if (pow((pos.x - this->x), 2) + pow((pos.y - this->y), 2) <= pow(this->rad, 2))
		return true;
	return false;
}

POINT RoundButton::GetLocation()
{
	return POINT{ this->x, this->y };
}
void RoundButton::SetLocation(int x, int y)
{
	this->x = x;
	this->y = y;
}