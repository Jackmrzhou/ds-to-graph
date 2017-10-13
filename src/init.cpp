#include <Windows.h>
#include <d2d1.h>
#include "init.hpp"
#include <dwrite.h>
#include <iostream>
#include "../tests/testHead.hpp"
#include "App.hpp"
#pragma comment(lib, "d2d1.lib")
using namespace std;

constexpr float UP_DOWN_DIS = 50.f;

HWND VisualDSApp::InitWindow(UINT Width, UINT Height, HINSTANCE hInstance)
{
	constexpr auto windowName = TEXT("data structure to graph");
	WNDCLASS wcls;
	wcls.cbClsExtra = 0;
	wcls.cbWndExtra = 0;
	wcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcls.hInstance = NULL;
	wcls.lpfnWndProc = VisualDSApp::WndProc;
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
		this
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

void VisualDSApp::InitD2D(HWND window)
{
	if (!m_pRenderTarget)
	{
		HRESULT hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		if (FAILED(hr))
		{
			MessageBox(window, "Create D2D factory failed!", "Error", 0);
			return;
		}

		// Obtain the size of the drawing area
		RECT rc;
		GetClientRect(window, &rc);
		// Create a Direct2D render target
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				window,
				D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
			),
			&m_pRenderTarget
		);
		if (FAILED(hr))
		{
			MessageBox(window, "Create render target failed!", "Error", 0);
			return;
		}

		// Create a brush
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_pBlackBrush
		);
		if (FAILED(hr))
		{
			MessageBox(window, "Create brush failed!", "Error", 0);
			return;
		}
	}
}

void VisualDSApp::InitDwrite()
{
	auto hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory)
	);
	if (FAILED(hr))
	{
		MessageBox(NULL, "Create Write Factory failed!", "Error", 0);
		return;
	}
	m_pWriteFactory->CreateTextFormat(
		L"Verdana",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&m_pTextForm
	);
	m_pTextForm->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextForm->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	//default text format
}