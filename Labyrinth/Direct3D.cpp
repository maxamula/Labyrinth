#include "Direct3D.h"

#include "Direct3D.h"
#include <iostream>

#define PI 3.14159265359
#define NWIDTH 10					// Arrow width


// Global declarations
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;

struct Vec
{
	float x, y;
};

void InitD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
}

void ReleaseD3D()
{
	d3ddev->Release();
	d3d->Release();
}

void DrawLine(int x1, int y1, int x2, int y2)
{
	VERTEX verts[2];

	verts[0].x = x1;
	verts[0].y = y1;
	verts[0].z = 0;
	verts[0].rhw = 1;
	verts[0].color = D3DCOLOR_XRGB(0, 0, 0);

	verts[1].x = x2;
	verts[1].y = y2;
	verts[1].z = 0;
	verts[1].rhw = 1;
	verts[1].color = D3DCOLOR_XRGB(0, 0, 0);

	d3ddev->SetFVF(VERTEX::FVF);
	d3ddev->DrawPrimitiveUP(D3DPT_LINELIST, 2, &verts, sizeof(VERTEX));
}

void DrawArrow(int xf, int yf, int xt, int yt)
{
	Vec linevec{ xt - xf, yt - yf };
	float linelen = sqrt(pow(linevec.x, 2) + pow(linevec.y, 2));
	float tPointOnLine = NWIDTH / (2 * (tanf(0.52f) / 2) * linelen);
	POINT pointonline;
	pointonline.x = xt + (-tPointOnLine * linevec.x);
	pointonline.y = yt + (-tPointOnLine * linevec.y);

	Vec normvec{ -linevec.y, linevec.x };
	float tNormal = NWIDTH / (2 * linelen);
	POINT left;
	left.x = pointonline.x + tNormal * normvec.x;
	left.y = pointonline.y + tNormal * normvec.y;
	POINT right;
	right.x = pointonline.x + (-tNormal * normvec.x);
	right.y = pointonline.y + (-tNormal * normvec.y);

	VERTEX verts[3];

	verts[0].x = xt;
	verts[0].y = yt;
	verts[0].z = 0;
	verts[0].rhw = 1;
	verts[0].color = D3DCOLOR_XRGB(0, 0, 0);

	verts[1].x = left.x;
	verts[1].y = left.y;
	verts[1].z = 0;
	verts[1].rhw = 1;
	verts[1].color = D3DCOLOR_XRGB(0, 0, 0);

	verts[2].x = right.x;
	verts[2].y = right.y;
	verts[2].z = 0;
	verts[2].rhw = 1;
	verts[2].color = D3DCOLOR_XRGB(0, 0, 0);

	d3ddev->SetFVF(VERTEX::FVF);
	d3ddev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 3, &verts, sizeof(VERTEX));
}

float SetLength(int x, int y, int len)
{
	float a = (len * sqrt(pow(x, 2) + pow(y, 2))) / (pow(x, 2) + pow(y, 2));
	return a;
}