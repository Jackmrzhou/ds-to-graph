#include <Windows.h>
#include <d2d1.h>
#include "init.hpp"
#include <dwrite.h>
#include <iostream>
#include "../tests/testHead.hpp"
#pragma comment(lib, "d2d1.lib")
using namespace std;

ID2D1Factory*			g_pD2DFactory = NULL;	
ID2D1HwndRenderTarget*	g_pRenderTarget = NULL;	
ID2D1SolidColorBrush*	g_pBlackBrush = NULL;
IDWriteFactory* g_pWriteFactory = NULL;

void InitDwrite();
constexpr float UP_DOWN_DIS = 50.f;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
		g_pRenderTarget->BeginDraw();
		g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
		ValidateRect(hwnd, NULL);
		g_pRenderTarget->EndDraw();
		return 0;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		case VK_DOWN:
			//g_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, UP_DOWN_DIS));
			//testArray();
			break;
		case VK_UP:
			//g_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, -UP_DOWN_DIS));
			//testArray();
			break;
		default:
			break;
		}
		return 0;
	}
	break;
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	
}
HWND InitWindow(int Width, int Height, HINSTANCE hInstance)
{
	constexpr auto windowName = TEXT("data structure to graph");
	WNDCLASS wcls;
	wcls.cbClsExtra = 0;
	wcls.cbWndExtra = 0;
	wcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcls.hInstance = NULL;
	wcls.lpfnWndProc = WndProc;
	wcls.lpszClassName = "graphics Window";
	wcls.lpszMenuName = NULL;
	wcls.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wcls);
	
	auto window = CreateWindow(
		"graphics Window",
		windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		Width,
		Height,
		NULL,//no console window
		NULL,
		hInstance,
		NULL
	);
	if (window == NULL)
	{
		MessageBox(NULL, TEXT("Create Window Failed!"), TEXT("ERROR"), 0);
	}
	InitD2D(window);
	//Initialize Direct2D
	InitDwrite();
	//Initialize Direct write
	ShowWindow(window, SW_NORMAL);
	UpdateWindow(window);
	return window;
}

void InitD2D(HWND window)
{
	if (!g_pRenderTarget)
	{
		HRESULT hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
		if (FAILED(hr))
		{
			MessageBox(window, "Create D2D factory failed!", "Error", 0);
			return;
		}

		// Obtain the size of the drawing area
		RECT rc;
		GetClientRect(window, &rc);
		// Create a Direct2D render target
		hr = g_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				window,
				D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
			),
			&g_pRenderTarget
		);
		if (FAILED(hr))
		{
			MessageBox(window, "Create render target failed!", "Error", 0);
			return;
		}

		// Create a brush
		hr = g_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&g_pBlackBrush
		);
		if (FAILED(hr))
		{
			MessageBox(window, "Create brush failed!", "Error", 0);
			return;
		}
	}
}

void Cleanup()
{

	SAFE_RELEASE(g_pRenderTarget);
	SAFE_RELEASE(g_pBlackBrush);
	SAFE_RELEASE(g_pD2DFactory);
	SAFE_RELEASE(g_pWriteFactory);
}

void InitDwrite()
{
	auto hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&g_pWriteFactory)
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Create Write Factory failed!", "Error", 0);
		return;
	}
}