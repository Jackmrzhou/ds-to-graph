#include "elements.hpp"
#include "App.hpp"
#include "init.hpp"
#include <cmath>
#include <utility>
#include "convert.cpp"
#include "Text.hpp"
//#if DEBUG
#include <string>
#include <iostream>
//#endif

Circle::Circle(VisualDSApp &a, float xx, float yy, float r)
	:app(a), x(xx), y(yy), radius(r),color(RED)
{
	app.m_pRenderTarget->CreateSolidColorBrush(color,&pBrush);
	CreatCircleGeo(pPathGeo);
}

Circle::Circle(VisualDSApp &a, float xx, float yy, float r, const D2D1::ColorF & c)
	:app(a), x(xx), y(yy), radius(r), color(c)
{
	app.m_pRenderTarget->CreateSolidColorBrush(color, &pBrush);
	CreatCircleGeo(pPathGeo);
}

Circle::Circle(VisualDSApp &a, float xx, float yy, float r, const D2D1::ColorF & c, const WCHAR * s)
	:app(a), x(xx), y(yy), radius(r), color(c)
{
	app.m_pRenderTarget->CreateSolidColorBrush(color, &pBrush);
	CreatCircleGeo(pPathGeo);
	pText = app.NewText(s);
}

Circle::~Circle() {
	SAFE_RELEASE(pPathGeo);
	SAFE_RELEASE(pBrush);
	if (pText != nullptr)
		delete pText;
}

HRESULT Circle::CreatCircleGeo(ID2D1PathGeometry * &pPathGeo)
{
	ID2D1GeometrySink *pSink = nullptr;
	auto hr = app.m_pD2DFactory->CreatePathGeometry(&pPathGeo);
	if (SUCCEEDED(hr))
	{
		hr = pPathGeo->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			pSink->BeginFigure(
				D2D1::Point2F(x - radius, y),
				D2D1_FIGURE_BEGIN_FILLED
			);
			pSink->AddArc(
				D2D1::ArcSegment(
					D2D1::Point2F(x + radius, y),
					D2D1::SizeF(radius, radius),
					.0f,
					D2D1_SWEEP_DIRECTION_CLOCKWISE,
					D2D1_ARC_SIZE_SMALL
				)
			);
			pSink->AddArc(
				D2D1::ArcSegment(
					D2D1::Point2F(x - radius, y),
					D2D1::SizeF(radius, radius),
					.0f,
					D2D1_SWEEP_DIRECTION_CLOCKWISE,
					D2D1_ARC_SIZE_SMALL
				)
			);
			pSink->EndFigure(D2D1_FIGURE_END_CLOSED);	
		}
		hr = pSink->Close();
		SAFE_RELEASE(pSink);
	}
	return hr;
}

void Circle::Draw() const
{
	//g_pRenderTarget->BeginDraw();
	app.m_pRenderTarget->DrawGeometry(pPathGeo, app.m_pBlackBrush);
	app.m_pRenderTarget->FillGeometry(pPathGeo, pBrush);
	if (pText != nullptr)
		pText->Draw(D2D1::RectF(
			x - radius / std::sqrt(2.f),
			y + radius / std::sqrt(2.f),
			x + radius / std::sqrt(2.f),
			y - radius / std::sqrt(2.f)
		));
	//auto hr = g_pRenderTarget->EndDraw();
	//return hr;
}

std::array<float, 3> Circle::info() const
{
	return std::array<float, 3>{x, y, radius};
}

Arrow::Arrow(VisualDSApp &a)
	:app(a), pPathGeo(nullptr)
{
}

Arrow::~Arrow()
{
	SAFE_RELEASE(pPathGeo);
}

HRESULT Arrow::CreateArrow(const Circle & c1, const Circle & c2)
{
	//create arrow from c1 to c2
	//make sure c1 and c2 are not crossed
	ID2D1GeometrySink *pSink = nullptr;
	auto hr = app.m_pD2DFactory->CreatePathGeometry(&pPathGeo);
	if (SUCCEEDED(hr))
	{
		hr = pPathGeo->Open(&pSink);
		if (SUCCEEDED(hr))
		{
			auto x1 = c1.info()[0], y1 = c1.info()[1], r1 = c1.info()[2];
			auto x2 = c2.info()[0], y2 = c2.info()[1], r2 = c2.info()[2];
			float x3, x4, y3, y4, x5, y5;
			if (x1 != x2)
			{
				float k = (y1 - y2) / (x1 - x2);
				int flag = x2 > x1 ? 1 : -1;
				x3 = x1 + (r1 / std::sqrt(1 + k*k)) * flag;
				y3 = flag * k*(r1 / std::sqrt(1 + k*k)) + y1;
				x4 = x2 - (r2 / std::sqrt(1 + k*k)) * flag;
				y4 = y2 - flag * k*(r2 / std::sqrt(1 + k*k));
				x5 = x4 - 7 * flag;
				y5 = k*(x5 - x1) + y1;
			}
			else
			{
				x5 = x3 = x4 = x1;
				y3 = y1 + (y1 < y2 ? r1 : -r1); 
				y4 = y2 + (y1 < y2 ? -r2 : r2);
				y5 = y4 - (y1 < y2 ? 7 : -7);
			}
			pSink->BeginFigure(
				D2D1::Point2F(x4, y4),
				D2D1_FIGURE_BEGIN_HOLLOW
			);
#define angle(x) x*3.14159265f/180
			pSink->AddLine(D2D1::Point2F(x3, y3));
			pSink->EndFigure(D2D1_FIGURE_END_OPEN);
			x1 = std::cos(angle(30))*(x5-x4) - std::sin(angle(30))*(y5-y4) + x4;
			y1 = std::sin(angle(30))*(x5-x4) + std::cos(angle(30))*(y5-y4) + y4;
			//simulate matrix transform
			pSink->BeginFigure(
				D2D1::Point2F(x4, y4),
				D2D1_FIGURE_BEGIN_HOLLOW
			);
			pSink->AddLine(D2D1::Point2F(x1, y1));
			pSink->EndFigure(D2D1_FIGURE_END_OPEN);
			pSink->BeginFigure(
				D2D1::Point2F(x4, y4),
				D2D1_FIGURE_BEGIN_HOLLOW
			);
			x1 = std::cos(angle(-30))*(x5-x4) - std::sin(angle(-30))*(y5-y4) + x4;
			y1 = std::sin(angle(-30))*(x5-x4) + std::cos(angle(-30))*(y5-y4) + y4;
			//simulate matrix transform
			pSink->AddLine(D2D1::Point2F(x1, y1));
			pSink->EndFigure(D2D1_FIGURE_END_OPEN);
			//no need to be closed
		}
		hr = pSink->Close();
		SAFE_RELEASE(pSink);
	}
	return hr;
}

void Arrow::Draw() const
{
	//g_pRenderTarget->BeginDraw();
	app.m_pRenderTarget->DrawGeometry(pPathGeo, app.m_pBlackBrush, 2.f);
	//auto hr = g_pRenderTarget->EndDraw();
	//return hr;
}

Cell::Cell(VisualDSApp &a, float h, float w, const D2D1_POINT_2F & p, size_t i,
	const D2D1::ColorF &c,	const WCHAR *s)
	:app(a), Height(h),Width(w),StartPoint(p),pIndex(to_WCHAR(i))
{
	app.m_pRenderTarget->CreateSolidColorBrush(c, &pBrush);
	pText = app.NewText(s);
	pIndexWStr = app.NewText(pIndex.get());
}

Cell::Cell(const Cell & c)
	:app(c.app),Height(c.Height), Width(c.Width), StartPoint(c.StartPoint),
	pIndex(static_cast<Cell>(c).pIndex.release()),pText(c.pText), pIndexWStr(c.pIndexWStr)
{
}

Cell::~Cell()
{
	SAFE_RELEASE(pBrush);
	if (pText != nullptr)
		delete pText;
	if (pIndexWStr != nullptr)
		delete pIndexWStr;
}

void Cell::Draw() const
{
	//g_pRenderTarget->BeginDraw();
	auto Rect = D2D1::RectF(
		StartPoint.x,
		StartPoint.y,
		StartPoint.x + Width,
		StartPoint.y - Height
	);
	app.m_pRenderTarget->DrawRectangle(Rect,app.m_pBlackBrush);
	app.m_pRenderTarget->FillRectangle(Rect, pBrush);
	pText->Draw(Rect);
	Rect.top += Height;
	Rect.bottom += Height;
	pIndexWStr->Draw(Rect);

	//auto hr = g_pRenderTarget->EndDraw();
	
	//return hr;
}
