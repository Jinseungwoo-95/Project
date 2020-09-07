#include "Bitmap.h"


Bitmap::Bitmap()
{
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}

Bitmap::Bitmap(const std::string fileDir)
{
	this->LoadBitmapByPath(fileDir);
}

Bitmap::Bitmap(const Bitmap & bitmap)
{
	this->LoadBitmapByPath(bitmap.GetFileDirectory());
}


Bitmap::~Bitmap()
{
	if (!this->Empty()) {
		DeleteObject(m_BitmapHandle);
	}
}

BOOL Bitmap::LoadBitmapByPath(const std::string fileDir)
{
	m_BitmapHandle = (HBITMAP)LoadImageA(nullptr, fileDir.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (this->Empty())
		return FALSE;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);	// m_BitmapHandle에 저장된 비트맵 정보를 m_BitmapInfo에 저장
	m_FileDir = fileDir;

	return TRUE;
}

BOOL Bitmap::Empty() const
{
	return m_BitmapHandle == nullptr;
}

HBITMAP Bitmap::GetBitmapHandle() const
{
	return m_BitmapHandle;
}

const BITMAP Bitmap::GetBitmapInfo() const
{
	return m_BitmapInfo;
}

std::string Bitmap::GetFileDirectory() const
{
	return m_FileDir;
}

void Bitmap::DrawBitmap(HDC hdc, int x, int y, int width, int height) const
{
	this->DrawBitmapByCropping(hdc, x, y, width, height, 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight);
}

void Bitmap::DrawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh, bool collision) const
{
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, m_BitmapHandle);

	if (collision == true)
	{
		HBITMAP oldBitBg;

		HDC bgDC = CreateCompatibleDC(hdc);		// 배경
		HBITMAP bgBitMap = CreateCompatibleBitmap(hdc, width, height);
		oldBitBg = (HBITMAP)SelectObject(bgDC, bgBitMap);

		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = 85;

		BitBlt(bgDC, 0, 0, width, height, hdc, x, y, SRCCOPY);

		TransparentBlt(bgDC, 0, 0, width, height, memDC, sx, sy, sw, sh, GetTransparentColor());


		AlphaBlend(hdc, x, y,
			width == 0 ? m_BitmapInfo.bmWidth : width,
			height == 0 ? m_BitmapInfo.bmHeight : height,
			bgDC, 0, 0, width, height, bf);

		DeleteObject(SelectObject(bgDC, oldBitBg));
		DeleteDC(bgDC);
	}
	else
	{
		TransparentBlt(hdc, x, y,
			width == 0 ? m_BitmapInfo.bmWidth : width,
			height == 0 ? m_BitmapInfo.bmHeight : height,
			memDC, sx, sy, sw, sh, GetTransparentColor());
	}

	DeleteDC(memDC);
}

void Bitmap::DrawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const
{
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, m_BitmapHandle);

	TransparentBlt(hdc, x, y,
		width == 0 ? m_BitmapInfo.bmWidth : width,
		height == 0 ? m_BitmapInfo.bmHeight : height,
		memDC, sx, sy, sw, sh, GetTransparentColor());

	DeleteDC(memDC);
}

void Bitmap::SetTransparentColor(DWORD color)
{
	m_TransparentColor = color;
}

DWORD Bitmap::GetTransparentColor() const
{

	return m_TransparentColor;
}
