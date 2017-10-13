#include "../src/elements.hpp"
#include "../src/ArrayType.hpp"
/*
void testArray()
{
	WCHAR *as[100];
	for (auto &it : as)
		it = new WCHAR[2]{ L"H" };
	ArrayType<WCHAR*, 100> testarray(as);
	g_pRenderTarget->BeginDraw();
	g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	testarray.Draw();
	g_pRenderTarget->EndDraw();
}
*/