#pragma once
#ifndef APP_H_
#define APP_H_
#include <Windows.h>
#include <vector>
#include "defines.hpp"
#include <d2d1.h>
#include <dwrite.h>
#include <memory>
using namespace std;
constexpr float TranslationDist = 50.f;
class Text;
class Circle;
class Cell;
class Base_DS;
/*
template<typename T, size_t size>
class ArrayType;
*/
#include "ArrayType.hpp"
#include "StackType.hpp"
#include "ListType.hpp"

class VisualDSApp
{
public:
	VisualDSApp(UINT H, UINT W);
	~VisualDSApp();

	friend class Circle;
	friend class Arrow;
	friend class Cell;
	friend class Text;

	template<typename T>
	Circle* NewCircle(float xx, float yy, float r,
		T value, const D2D1::ColorF &c = WHITE){
		return new Circle(*this, xx, yy, r, c, value);
	}
	Arrow *NewArrow();
	Cell CreateCell(float h, float w, const D2D1_POINT_2F &p, size_t i,
		const WCHAR *s = nullptr, const D2D1::ColorF &c = WHITE);
	Text CreateText(const WCHAR * s, const D2D1::ColorF &c = BLACK);
	Text* NewText(const WCHAR * s, const D2D1::ColorF &c = BLACK);
	template<typename T>
	Cell* NewCell(float h, float w, const D2D1_POINT_2F &p, size_t i,
		T value, const D2D1::ColorF &c = WHITE)
	{
		return new Cell(*this, h, w, p, i, c, value);
	}

	template<typename _T, size_t _size>
	unique_ptr<ArrayType<_T, _size>> NewArray(_T* pHead) {
		auto a = new ArrayType<_T, _size>(*this, pHead);
		ObjList.push_back(a);
		return unique_ptr<ArrayType<_T, _size>>(a);
	}

	template<class _Tc,typename _T, size_t _size>
	unique_ptr<StackType<_Tc, _T, _size>> NewStack(_T* pHead) {
		auto s = new StackType<_Tc, _T, _size>(*this, NewArray<_T, _size>(pHead));
		ObjList.push_back(s);
		return unique_ptr<StackType<_Tc, _T, _size>>(s);
	}

	template<typename T>
	unique_ptr<ListType<T>> NewList(T *pHead) {
		auto s = new ListType<T>(*this, pHead);
		ObjList.push_back(s);
		return unique_ptr<ListType<T>>(s);
	}

	template<typename T>
	unique_ptr<BinaryTreeType<T>> NewTree(T *pHead) {
		auto s = new BinaryTreeType<T>(*this, pHead);
		ObjList.push_back(s);
		return unique_ptr<BinaryTreeType<T>>(s);
	}

	void OnRender();
	void RunMessageLoop();
	D2D1_SIZE_F GetSize();

private:
	HWND window;
	ID2D1Factory*			m_pD2DFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	ID2D1SolidColorBrush*	m_pBlackBrush;
	IDWriteFactory*			m_pWriteFactory;
	IDWriteTextFormat*		m_pTextForm;

	D2D1_POINT_2F Coor_Origin = D2D1::Point2F(0.f, 0.f);
	vector<Base_DS*> ObjList;

private:
	void InitDwrite();
	void VisualDSApp::InitD2D(HWND window);
	HWND InitWindow(UINT Width, UINT Height, HINSTANCE hInstance = NULL);
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);

	void UpTranslation();
	void DownTranslation();
	void LeftTranslation();
	void RightTranslation();

	void ThrowError();
};
#endif // !APP_H_