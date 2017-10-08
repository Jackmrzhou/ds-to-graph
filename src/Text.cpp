#include "Text.hpp"
#include "init.hpp"
#include <dwrite.h>
#include "elements.hpp"
#pragma comment(lib, "dwrite.lib")
Text::Text(const WCHAR * t)
	:text(t), text_length((UINT32)wcslen(t))
{
	InitDText(BLACK);
}
Text::Text(const WCHAR * t, const D2D1::ColorF &c)
	:text(t), text_length((UINT32)wcslen(t))
{
	InitDText(c);
}

Text::Text(const Text * t)
{
	*this = *t;
}

Text::~Text()
{
	SAFE_RELEASE(pTextForm);
	SAFE_RELEASE(pBrush);
}

void Text::Draw(const D2D1_RECT_F &layoutRect) const
{
	//g_pRenderTarget->BeginDraw();
	g_pRenderTarget->DrawText(
		text,        // The string to render.
		text_length,    // The string's length.
		pTextForm,    // The text format.
		layoutRect,       // The region of the window where the text will be rendered.
		pBrush     // The brush used to draw the text.
	);
	//auto hr = g_pRenderTarget->EndDraw();
	//return hr;
	//BeginDraw and EndDraw are better called by user 
}

void Text::InitDText(const D2D1::ColorF & c)
{
	g_pWriteFactory->CreateTextFormat(
		L"Gabriola",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"en-us",
		&pTextForm
	);
	pTextForm->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextForm->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	g_pRenderTarget->CreateSolidColorBrush(c, &pBrush);
}
