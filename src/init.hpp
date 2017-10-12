#pragma once
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}
#ifndef INIT_H
#define INIT_H

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>


HWND InitWindow(int Width, int Height, HINSTANCE hInstance);
void InitD2D(HWND window);
void Cleanup();
extern ID2D1Factory*			g_pD2DFactory;
extern ID2D1HwndRenderTarget*	g_pRenderTarget;
extern ID2D1SolidColorBrush*	g_pBlackBrush;
extern IDWriteFactory* g_pWriteFactory;
#endif // !INIT_H
