#include "../src/elements.hpp"
#include "../src/ArrayType.cpp"
void testArray()
{
	WCHAR *as[40];
	for (auto &it : as)
		it = new WCHAR[4]{ L"H" };
	ArrayType<WCHAR*, 40> testarray(as);
	g_pRenderTarget->BeginDraw();
	testarray.Draw();
	g_pRenderTarget->EndDraw();
}