#pragma once
#define RED D2D1::ColorF::Red
#define BLACK D2D1::ColorF::Black
#define WHITE D2D1::ColorF::White
#ifndef _ICON_H
#define _ICON_H
#include <d2d1.h>
#include <array>
#include "Text.hpp"
#include<memory>
class Container
{
public:

private:

};

class Circle
{
public:
	Circle(float xx, float yy, float r);
	Circle(float xx, float yy, float r, const D2D1::ColorF &c);
	Circle(float xx, float yy, float r, const D2D1::ColorF &c, const WCHAR *s);
	Circle(float xx, float yy, float r, const D2D1::ColorF &c, const Text *t);
	~Circle();
	void Draw() const;
	std::array<float, 3> info() const;

private:
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
	Arrow();
	~Arrow();
	HRESULT CreateArrow(const Circle & c1, const Circle &c2);
	void Draw() const;
private:
	ID2D1PathGeometry *pPathGeo;
};

class Cell
{
public:
	Cell(float h, float w, const D2D1_POINT_2F &p, size_t i, const D2D1::ColorF &c,
		const WCHAR * s);
	~Cell();
	void Draw() const;
private:
	float Height, Width;
	D2D1_POINT_2F StartPoint;
	std::unique_ptr<WCHAR> pIndex;
	Text *pIndexWStr= nullptr;
	Text *pText = nullptr;
	ID2D1SolidColorBrush *pBrush = nullptr;
};
#endif // !_ICON_H
