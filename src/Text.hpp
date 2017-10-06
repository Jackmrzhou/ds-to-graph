#pragma once
#ifndef TEXT_H
#define TEXT_H
#include <dwrite.h>
#include "init.hpp"
class Text
{
public:
	Text(const WCHAR *t);
	Text(const WCHAR *t, const D2D1::ColorF &c);
	Text(const Text *t);
	~Text();
	HRESULT Draw(const D2D1_RECT_F &layoutRect) const;
private:
	const WCHAR * text;
	UINT32 text_length;
	IDWriteTextFormat * pTextForm = nullptr;
	ID2D1SolidColorBrush *pBrush = nullptr;
private:
	void InitDText(const D2D1::ColorF &c);
};
#endif // !TEXT_H
