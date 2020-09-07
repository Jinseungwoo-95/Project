#include "Cookie.h"

void Cookie::Init(Character * pChar)
{
	mBitmap.LoadBitmapByPath("Resource/Attack.bmp");
	mPosiX = 0;
	mPosiY = 0;
	m_Collision = false;
	m_pChar = pChar;
}

void Cookie::Init()
{
}

void Cookie::Update(float dt)
{
	if (m_Act)
	{
		mPosiX -= 8;
		if (mPosiX <= 0)
			m_Act = false;

		// 某腐磐客 面倒 贸府
		RECT dest;
		RECT rect = { mPosiX, mPosiY, mPosiX + 40, mPosiY + 40 };
		if (IntersectRect(&dest, &rect, &m_pChar->GetRect()))
		{
			m_Collision = true;
			++g_Bullet;
		}
	}
}

void Cookie::Render(HDC hdc, float dt)
{
	if (m_Act)
	{
		if (m_Collision)
		{
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 40, 40, 0, 40, 40, 40);
			m_Act = false;
		}
		else
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 40, 40, 0, 0, 40, 40);
	}
}

void Cookie::Destroy()
{
}

void Cookie::SetPosition(int x, int y)
{
	mPosiX = x;
	mPosiY = y;
	m_Act = true;
	m_Collision = false;
}

BOOL Cookie::GetAct()
{
	return m_Act;
}

Cookie::Cookie()
{
}


Cookie::~Cookie()
{
}
