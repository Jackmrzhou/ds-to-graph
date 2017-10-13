#pragma once
#ifndef TEXT_H
#define TEXT_H
#include <dwrite.h>
#include <d2d1.h>
class VisualDSApp;
class Text
{
public:
	Text(VisualDSApp &a,const WCHAR *t);
	Text(VisualDSApp &a,const WCHAR *t, const D2D1::ColorF &c);
	~Text();
	void Draw(const D2D1_RECT_F &layoutRect) const;
private:
	VisualDSApp &app;
	const WCHAR * text;
	UINT32 text_length;
	//IDWriteTextFormat * pTextForm = nullptr;
	ID2D1SolidColorBrush *pBrush = nullptr;
private:
	void InitDText(const D2D1::ColorF &c);
};
#endif // !TEXT_H
