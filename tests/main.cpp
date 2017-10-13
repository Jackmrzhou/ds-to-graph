#include <iostream>
#include "../src/init.hpp"
#include "testHead.hpp"
#include "../src/App.hpp"
#include "../src/Base.hpp"
using namespace std;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	VisualDSApp app(600, 800);
	
	WCHAR *ws[100];
	for (auto &it : ws)
		it = new WCHAR[2]{ L"H" };
	auto p =app.NewArray<WCHAR*, 100>(ws);
	app.OnRender();
	app.RunMessageLoop();
	return 0;
}