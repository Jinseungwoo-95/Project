#include "Fire.h"
#include "Character2.h"
#pragma warning(disable:4996)

void Fire::Init(Character2 * pChar)
{
	mPosiX = 0;
	mPosiY = 0;
	mBitmap.LoadBitmapByPath("Resource/Fire.bmp");
	m_Act = false;
	m_pChar = pChar;
	m_Collision = false;
	m_SpriteTime = 0;
	m_Direction = VERTICAL;
}

BOOL Fire::GetAct()
{
	return m_Act;
}

void Fire::SetAct(BOOL value)
{
	m_Act = value;
}

void Fire::SetDirection(Direction value)
{
	m_Direction = value;
}

void Fire::Init()
{
}

void Fire::Update(float dt)
{
	if (m_Act)
	{
		RECT fireRect;
		switch (m_Direction)
		{
		case VERTICAL:
			mPosiY += 5;
			fireRect = { mPosiX, mPosiY, mPosiX + 30, mPosiY + 50 };
			break;
		case LEFT:
			mPosiX += cos(45.0 * 3.14 / 180) * -5;
			mPosiY += cos(45.0 * 3.14 / 180) * 5;
			//mPosiX -= 5;
			//mPosiY += 5;
			fireRect = { mPosiX, mPosiY, mPosiX + 40, mPosiY + 40 };
			break;
		case RIGHT:
			mPosiX += cos(45.0 * 3.14 / 180) * 5;
			mPosiY += cos(45.0 * 3.14 / 180) * 5;
			fireRect = { mPosiX, mPosiY, mPosiX + 40, mPosiY + 40 };
			break;
		}

		// 캐릭터와 충돌체크
		RECT dest;
		
		if (IntersectRect(&dest, &fireRect, &m_pChar->GetRect()))
		{
			m_Collision = true;
			m_pChar->MinusHP(1);
		}

		// 땅에 닿으면 없애기
		if (mPosiY >= 680)
		{
			m_Act = false;
		}
	}
}

void Fire::Render(HDC hdc, float dt)
{
	if (m_Act)
	{
		//char a[128];
		//sprintf(a, "ani : %d", m_SpriteAnimNow);
		//TextOutA(hdc, mPosiX, mPosiY - 15, a, strlen(a));
		//Rectangle(hdc, mPosiX, mPosiY, mPosiX + 30, mPosiY + 50);	// 렉탱글도 다시 변경하자
		// 사이즈 : 수직 30 / 50	대각선 40/40	폭파는 30/30
		
		if (m_Collision)
		{
			for (int i = 0; i < 6; ++i)
			{
				mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY + 20, 50, 50, 30 * i, 50, 30, 30);
			}
			m_Act = false;
			m_Collision = false;
		}
		else if(m_Direction == VERTICAL)
		{
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 30, 50, 0, 0, 30, 50);
		}
		else if (m_Direction == LEFT)
		{
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 40, 40, 30, 0, 40, 40);
		}
		else
		{
			mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 40, 40, 70, 0, 40, 40);
		}


	}
}

void Fire::Destroy()
{
}

Fire::Fire()
{
}


Fire::~Fire()
{
}
