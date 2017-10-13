#pragma once
#include "defines.hpp"
#ifndef _ELEMENTS_H_
#define _ELEMENTS_H_
#include <d2d1.h>
#include <array>
#include <memory>
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
	Circle(VisualDSApp &a, float xx, float yy, float r, const D2D1::ColorF &c, const WCHAR *s);
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
	void Draw() const;
private:
	VisualDSApp &app;
	ID2D1PathGeometry *pPathGeo;
};

class Cell
{
public:
	Cell(VisualDSApp &a, float h, float w, const D2D1_POINT_2F &p, size_t i,
		const D2D1::ColorF &c,	const WCHAR * s);
	Cell(const Cell&c);
	~Cell();
	void Draw() const;
private:
	VisualDSApp &app;
	float Height, Width;
	D2D1_POINT_2F StartPoint;
	std::unique_ptr<WCHAR> pIndex;
	Text *pIndexWStr= nullptr;
	Text *pText = nullptr;
	ID2D1SolidColorBrush *pBrush = nullptr;
};
#endif // 
