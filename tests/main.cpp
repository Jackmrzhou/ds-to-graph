#include <iostream>
#include "../src/init.hpp"
#include "testHead.hpp"
using namespace std;

void TestDraw()
{
	g_pRenderTarget->BeginDraw();

	g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	g_pRenderTarget->DrawRectangle(
		D2D1::RectF(100.f, 100.f, 500.f, 500.f),
		g_pBlackBrush);

	HRESULT hr = g_pRenderTarget->EndDraw();
	if (FAILED(hr))
	{
		MessageBox(NULL, "Draw failed!", "Error", 0);
		return;
	}
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	auto window = InitWindow(800, 600, hInstance);
	//TestDraw();
	//TestElements();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	testArray();
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);  
		DispatchMessage(&msg);
	}
	return msg.wParam;
}