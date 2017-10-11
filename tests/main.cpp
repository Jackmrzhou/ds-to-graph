#include <iostream>
#include "../src/init.hpp"
#include "DS_tests.cpp"
#include "TestElements.cpp"
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

int main()
{
	auto window = InitWindow(800, 600);
	//TestDraw();
	TestElements();
	system("pause");
	Cleanup();
	return 0;
}