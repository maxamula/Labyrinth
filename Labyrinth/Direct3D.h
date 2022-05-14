#pragma once
#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>

// Global
extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;

void InitD3D(HWND hWnd);
void ReleaseD3D();

void DrawLine(int x1, int y1, int x2, int y2);
void DrawArrow(int x1, int y1, int x2, int y2);

float SetLength(int x, int y, int len);

struct VERTEX {
    float x, y, z, rhw;
    D3DCOLOR color;
    static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
};