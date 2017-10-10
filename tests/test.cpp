#include <iostream>
#include "../src/init.hpp"
#include "../src/elements.hpp"
#include "../src/Text.hpp"
#include "../src/ArrayType.cpp"
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
	/*
	auto testCircle1 = new Circle(100, 100, 40, BLACK,new Text(L"H", WHITE));
	auto testCircle2 =new Circle(250, 230, 40,RED,new Text(L"P"));
	testCircle1->Draw();
	testCircle2->Draw();
	Arrow testArrow;
	testArrow.CreateArrow(*testCircle1, *testCircle2);
	testArrow.Draw();
	*/
	/*
	Text testText(L"Hello World!");
	testText.Draw(D2D1::RectF(
		400.f, 100.f, 500.f, 200.f
	));
	*/
	//auto testCell = new Cell(100, 100, D2D1::Point2F(300, 400), 0, RED,L"Test");
	//testCell->Draw();
	WCHAR *as[10] = { L"J",L"A",L"C",L"K",L"M",L"R",L"Z",L"H",L"O",L"U" };
	ArrayType<WCHAR*, 10> testarray(as);
	g_pRenderTarget->BeginDraw();
	testarray.Draw();
	g_pRenderTarget->EndDraw();
	/*auto hr = g_pRenderTarget->EndDraw();
	if (SUCCEEDED(hr))
		cout << "SUCCEEDED" << endl;*/
	system("pause");
	
	//delete testCircle1;
	//delete testCircle2;
	//delete testCell;
	Cleanup();
	return 0;
}