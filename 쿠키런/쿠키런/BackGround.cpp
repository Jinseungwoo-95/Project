#include "BackGround.h"
#pragma warning(disable : 4996)


void BackGround::Init(char * imageName, RECT rect)
{
	const char* path = "Resource/";
	char filePath[256];
	sprintf(filePath, "%s%s", path, imageName);
	GetBitmap()->LoadBitmapByPath(filePath);

	mPosiX = rect.left;
	mPosiY = rect.top;

	m_Width = rect.right - rect.left;
	m_Height = rect.bottom - rect.top;
}

void BackGround::Init()
{
}

void BackGround::Update(float dt)
{
}

void BackGround::Render(HDC hdc, float dt)
{
	GetBitmap()->DrawBitmap(hdc, mPosiX, mPosiY, m_Width, m_Height);
}

void BackGround::Destroy()
{
}

void BackGround::SetTransparenColor(DWORD color)
{
	GetBitmap()->SetTransparentColor(color);
}

BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}
