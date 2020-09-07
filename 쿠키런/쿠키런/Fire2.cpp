#include "Fire2.h"
#include "Character2.h"


void Fire2::Init(Character2 * pChar)
{
	mBitmap.LoadBitmapByPath("Resource/BossAttack.bmp");
	m_pChar = pChar;
	m_Remove = false;
}

void Fire2::Init()
{
}

void Fire2::Update(float dt)
{
	mPosiX -= 5;

	RECT dest;
	RECT fireRect = { mPosiX, mPosiY, mPosiX + 50, mPosiY + 50 };

	if (IntersectRect(&dest, &fireRect, &m_pChar->GetRect()))
	{
		m_Remove = true;
		m_pChar->MinusHP(1);
	}

	if (mPosiX <= -50)
	{
		m_Remove = true;
	}
}

void Fire2::Render(HDC hdc, float dt)
{
	if (!m_Remove)
	{
		//Rectangle(hdc, mPosiX, mPosiY, mPosiX + 50, mPosiY + 50);
		mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 50, 50, 50, 0, 50, 50);
	}
	else
	{
		for (int i = 0; i < 6; ++i)
		{
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 50, 50, 50 * i, 50, 50, 50);
		}
	}
}

void Fire2::Destroy()
{
}

BOOL Fire2::GetRemove()
{
	return m_Remove;
}

Fire2::Fire2()
{
}


Fire2::~Fire2()
{
}
