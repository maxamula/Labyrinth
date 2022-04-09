#include "Direct3D.h"
#include <iostream>

// Global declarations
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;

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