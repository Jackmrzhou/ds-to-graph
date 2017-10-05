#include <iostream>
#include "../src/init.hpp"
#include "../src/elements.hpp"
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
	Circle testCircle1(100, 100, 20, BLACK), testCircle2(150,130,20);
	testCircle1.Draw();
	testCircle2.Draw();
	Arrow testArrow;
	testArrow.CreateArrow(testCircle1, testCircle2);
	testArrow.Draw();
	system("pause");
	Cleanup();
	return 0;
}