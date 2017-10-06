#pragma once
#define RED D2D1::ColorF::Red
#define BLACK D2D1::ColorF::Black
#define WHITE D2D1::ColorF::White
#ifndef _ICON_H
#define _ICON_H
#include <d2d1.h>
#include <array>
#include "Text.hpp"
class Icon
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
	HRESULT Draw() const;
	std::array<float, 3> info() const;

private:
	float x, y;
	float radius;
	D2D1::ColorF color;
	ID2D1SolidColorBrush *pBrush = nullptr;
	ID2D1PathGeometry *pPathGeo = nullptr;
	Text *pText;

private:
	HRESULT CreatCircleGeo(ID2D1PathGeometry *&pPathGeo);
};

class Arrow
{
public:
	Arrow();
	~Arrow();
	HRESULT CreateArrow(const Circle & c1, const Circle &c2);
	HRESULT Draw() const;
private:
	ID2D1PathGeometry *pPathGeo;
};
#endif // !_ICON_H
