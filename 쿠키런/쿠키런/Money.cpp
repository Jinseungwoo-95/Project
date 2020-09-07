#include "Money.h"



void Money::Init(Character * pChar)
{
	mBitmap.LoadBitmapByPath("Resource/Effect.bmp");
	mPosiX = 0;
	mPosiY = 0;
	m_AniCount = 0;
	m_AniNum = 0;
	m_Collision = false;
	m_pChar = pChar;
}

void Money::Init()
{
}

void Money::Update(float dt)
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
			//m_pChar->AddMoney();
		}

		if (m_AniCount + 250 < GetTickCount())
		{
			m_AniCount = GetTickCount();
			m_AniNum = ++m_AniNum > 5 ? 0 : m_AniNum;
		}
	}

}

void Money::Render(HDC hdc, float dt)
{
	if (m_Act)
	{
		//Rectangle(hdc, mPosiX, mPosiY, mPosiX + 40, mPosiY + 40);
		if (m_Collision)
		{
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 40, 40, 0, 128, 64, 64);
			m_Act = false;
		}
		else
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 40, 40, 64 * m_AniNum, 0, 64, 64);
	}
}

void Money::Destroy()
{
	
}

void Money::SetPosition(int x, int y)
{
	mPosiX = x;
	mPosiY = y;
	m_Act = true;
	m_Collision = false;
}

BOOL Money::GetAct()
{
	return m_Act;
}

Money::Money()
{

}


Money::~Money()
{
}
