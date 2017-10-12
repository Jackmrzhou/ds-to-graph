#pragma once
#ifndef CONVERT_H_
#define CONVERT_H_
#include <cwchar>
#include <memory>
#include <sstream>
using namespace std;
using WCHAR = wchar_t;
template<typename T>
unique_ptr<WCHAR> to_WCHAR(T value)
//deal with int, float, double and other types
{
	wstringstream ws;
	ws << value;
	//let wstringstream help us deal with all cases.
	auto s = ws.str();
	unique_ptr<WCHAR> pWCHAR(new WCHAR[s.size() + 1]);
	wcscpy_s(pWCHAR.get(), s.size() + 1, s.c_str());
	return pWCHAR;
}
#endif // !CONVERT_H_
