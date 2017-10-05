#pragma once
#ifndef INIT_H
#define INIT_H

#include <Windows.h>
#include <d2d1.h>
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

HWND InitWindow(int Width, int Height);
void InitD2D(HWND window);
void Cleanup();
extern ID2D1Factory*			g_pD2DFactory;
extern ID2D1HwndRenderTarget*	g_pRenderTarget;
extern ID2D1SolidColorBrush*	g_pBlackBrush;
#endif // !INIT_H
