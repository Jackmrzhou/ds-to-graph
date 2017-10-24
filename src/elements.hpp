#pragma once
#include "defines.hpp"
#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_
#include <d2d1.h>
#include <array>
#include <memory>
#include "convert.cpp"
class VisualDSApp;
class Text;
class Container
{
public:

private:

};

class Circle
{
public:
	Circle(VisualDSApp &a, float xx, float yy, float r);
	Circle(VisualDSApp &a, float xx, float yy, float r, const D2D1::ColorF &c);
	template<typename T>
	Circle(VisualDSApp &a, float xx, float yy, float r, const D2D1::ColorF &c, T value) 
		:app(a), x(xx), y(yy), radius(r), color(c), pValue(to_WCHAR(value))
	{
		app.m_pRenderTarget->CreateSolidColorBrush(color, &pBrush);
		CreatCircleGeo(pPathGeo);
		pText = app.NewText(pValue.get());
	}
	~Circle();
	void Draw() const;
	std::array<float, 3> info() const;

private:
	VisualDSApp &app;
	float x, y;
	float radius;
	D2D1::ColorF color;
	ID2D1SolidColorBrush *pBrush = nullptr;
	ID2D1PathGeometry *pPathGeo = nullptr;
	std::unique_ptr<WCHAR> pValue;
	Text *pText = nullptr;

private:
	HRESULT CreatCircleGeo(ID2D1PathGeometry *&pPathGeo);
};

class Arrow
{
public:
	Arrow(VisualDSApp &a);
	~Arrow();
	HRESULT CreateArrow(const Circle & c1, const Circle &c2);
	HRESULT CreateArrow(const Circle *c1, const Circle *c2) {
		return CreateArrow(*c1, *c2);
	}
	void Draw() const;
private:
	VisualDSApp &app;
	ID2D1PathGeometry *pPathGeo;
};

class Cell
{
public:
	template<typename T>
	Cell(VisualDSApp &a, float h, float w, const D2D1_POINT_2F &p, size_t i,
		const D2D1::ColorF &c, T value)
			:app(a), Height(h), Width(w), StartPoint(p), pIndex(to_WCHAR(i)), pValue(to_WCHAR(value))
		{
			app.m_pRenderTarget->CreateSolidColorBrush(c, &pBrush);
			pText = app.NewText(pValue.get());
			pIndexWStr = app.NewText(pIndex.get());
		}
	Cell(const Cell&c);
	~Cell();
	void Draw() const;
	void SetColor(const D2D1::ColorF & c);
	template<typename T>
	void SetValue(T value)
	{
		pValue.reset(nullptr);
		pValue = to_WCHAR(value);
		if (pText != nullptr)
			delete pText;
		pText = app.NewText(pValue.get());
	}
private:
	VisualDSApp &app;
	float Height, Width;
	D2D1_POINT_2F StartPoint;
	std::unique_ptr<WCHAR> pIndex;
	std::unique_ptr<WCHAR> pValue;
	Text *pIndexWStr= nullptr;
	Text *pText = nullptr;
	ID2D1SolidColorBrush *pBrush = nullptr;
};
#endif // 
