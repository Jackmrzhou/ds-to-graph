#include <d2d1.h>
#include "elements.hpp"
#ifndef __ARRAYTYPE__
#define __ARRAYTYPE__
template<typename T, size_t size>
class ArrayType
{
public:
	ArrayType(const T *h);
	void Draw() const;
private:
	const T* pArrayHead;
};

constexpr float startX = 50.f;
constexpr float startY = 50.f;
constexpr float CellHeight = 40.f;
constexpr float CellWidth = 50.f;
template<typename T, size_t size>
inline ArrayType<T, size>::ArrayType(const T * h)
	:pArrayHead(h)
{
}

template<typename T, size_t size>
void ArrayType<T, size>::Draw() const
{
	D2D1_POINT_2F NowPoint=D2D1::Point2F(startX,startY);
	for (size_t index = 0; index < size; ++index)
	{
		//Check boundary
		if (NowPoint.x + CellWidth > g_pRenderTarget->GetSize().width)
		{
			NowPoint.x = startX; 
			NowPoint.y += CellHeight * 2;
		}
		if (NowPoint.y > g_pRenderTarget->GetSize().height)
			;
			//TODO:ERROR handle
		auto nowCell = new Cell(
			CellHeight,
			CellWidth,
			NowPoint,
			index,
			RED,
			*(pArrayHead + index));
		nowCell->Draw();
		delete nowCell;
		NowPoint.x += CellWidth;
	}
}
#endif // !__ARRAYTYPE__