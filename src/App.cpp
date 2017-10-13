#include "App.hpp"
#include "init.hpp"
#include "elements.hpp"
#include "Text.hpp"
#include <d2d1.h>
#include <dwrite.h>
#include "Base.hpp"

VisualDSApp::VisualDSApp(UINT H, UINT W)
	:window(InitWindow(W, H))
{
}

VisualDSApp::~VisualDSApp()
{
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pBlackBrush);
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pWriteFactory);
	SAFE_RELEASE(m_pTextForm);
}

Circle VisualDSApp::CreateCircle(float xx, float yy, float r, const WCHAR * s,const D2D1::ColorF & c)
{
	return Circle(*this, xx, yy, r, c, s);
}

Arrow VisualDSApp::CreateArrow()
{
	return Arrow(*this);
}

Cell VisualDSApp::CreateCell(float h, float w, const D2D1_POINT_2F & p, 
	size_t i, const WCHAR * s, const D2D1::ColorF & c)
{
	return Cell(*this, h, w, p, i, c, s);
}

Text VisualDSApp::CreateText(const WCHAR * s, const D2D1::ColorF & c)
{
	return Text(*this, s, c);
}

Text * VisualDSApp::NewText(const WCHAR * s, const D2D1::ColorF & c)
{
	return new Text(*this, s, c);
}

Cell * VisualDSApp::NewCell(float h, float w, const D2D1_POINT_2F & p, size_t i, const WCHAR * s, const D2D1::ColorF & c)
{
	return new Cell(*this, h, w, p, i,c, s);
}

void VisualDSApp::OnRender()
{
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	for (auto o : ObjList)
		o->Draw();
	m_pRenderTarget->EndDraw();
}

void VisualDSApp::RunMessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

D2D1_SIZE_F VisualDSApp::GetSize()
{
	return m_pRenderTarget->GetSize();
}

LRESULT CALLBACK VisualDSApp::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_CREATE)
	{
		LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
		VisualDSApp *pApp = (VisualDSApp *)pcs->lpCreateParams;

		::SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			PtrToUlong(pApp)
		);

		return 1;
	}
	else {
		VisualDSApp *pApp = reinterpret_cast<VisualDSApp *>(static_cast<LONG_PTR>(
			::GetWindowLongPtrW(
				hwnd,
				GWLP_USERDATA
			)));
		if (pApp) {
			switch (msg)
			{
			case WM_PAINT:
				//pApp->OnRender();
				ValidateRect(hwnd, NULL);
				return 0;
			case WM_KEYDOWN:
			{
				switch (wParam)
				{
				case VK_ESCAPE:
					SendMessage(hwnd, WM_CLOSE, 0, 0);
					break;
				case VK_DOWN:
					pApp->DownTranslation();
					break;
				case VK_UP:
					pApp->UpTranslation();
					break;
				default:
					break;
				}
				return 0;
			}
			break;
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			default:
				break;
			}
		}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void VisualDSApp::UpTranslation()
{
	Coor_Origin.y -= TranslationDist;
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0.f, Coor_Origin.y));
	OnRender();
}

void VisualDSApp::DownTranslation()
{
	Coor_Origin.y += TranslationDist;
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0.f, Coor_Origin.y));
	OnRender();
}