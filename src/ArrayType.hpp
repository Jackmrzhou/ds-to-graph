#pragma once
#ifndef __ARRAYTYPE__
#define __ARRAYTYPE__
#include <array>
#include <memory>
#include "Base.hpp"
#include "elements.hpp"
using namespace std;

class VisualDSApp;

template<typename T, size_t size>
class ArrayType:public Base_DS
{
public:
	ArrayType(VisualDSApp &a,const T *h);
	virtual void Draw() const;
	void SetColor(size_t index, const D2D1::ColorF &c);
private:
	VisualDSApp &app;
	const T* pArrayHead;
	void constructArray();
	array<unique_ptr<Cell>, size> Cells;
};

constexpr float startX = 50.f;
constexpr float startY = 50.f;
constexpr float CellHeight = 40.f;
constexpr float CellWidth = 50.f;
template<typename T, size_t size>
ArrayType<T, size>::ArrayType(VisualDSApp &a, const T * h)
	:app(a), pArrayHead(h)
{
	constructArray();
}

template<typename T, size_t size>
void ArrayType<T, size>::Draw() const
{
	for (auto &it : Cells)
		it.get()->Draw();
}

template<typename T, size_t size>
inline void ArrayType<T, size>::SetColor(size_t index, const D2D1::ColorF &c)
{
	(*Cells[index]).SetColor(index, c);
}

template<typename T, size_t size>
inline void ArrayType<T, size>::constructArray()
{
	D2D1_POINT_2F NowPoint = D2D1::Point2F(startX, startY);
	for (size_t index = 0; index < size; ++index)
	{
		//Check boundary
		if (NowPoint.x + CellWidth > app.GetSize().width)
		{
			NowPoint.x = startX;
			NowPoint.y += CellHeight * 2;
		}
		auto nowCell = app.NewCell(
			CellHeight,
			CellWidth,
			NowPoint,
			index,
			*(pArrayHead + index),
			RED);
		//default set to red color
		Cells[index] = std::move(unique_ptr<Cell>(nowCell));
		NowPoint.x += CellWidth;
	}
}
#endif // !__ARRAYTYPE__