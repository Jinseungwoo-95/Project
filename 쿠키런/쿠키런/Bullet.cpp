#include "Bullet.h"

void Bullet::Init(Boss * pBoss)
{
	m_pBoss = pBoss;
	mPosiX = 0;
	mPosiY = 0;
	m_Act = false;
	mBitmap.LoadBitmapByPath("Resource/Attack.bmp");
	m_Direction = RIGHT;
}

void Bullet::Init()
{
}

void Bullet::Update(float dt)
{
	if (m_Act)
	{
		if (m_Direction == RIGHT)
		{
			mPosiX += 15;
			if (mPosiX >= 1280)
				m_Act = false;
		}
		else
		{
			mPosiX -= 15;
			if (mPosiX <= 0)
				m_Act = false;
		}

		RECT dest;
		RECT bulletRect = { mPosiX + 5, mPosiY + 5, mPosiX + 45, mPosiY + 45 };
		if (m_pBoss->GetType() != CHANGE)
		{
			if (IntersectRect(&dest, &bulletRect, &m_pBoss->GetRect()))
			{
				m_Act = false;
				m_pBoss->MinusHP(1);
			}
		}
	}
}

void Bullet::Render(HDC hdc, float dt)
{
	if(m_Act)
	{
		//Rectangle(hdc, mPosiX+5, mPosiY+5, mPosiX + 45, mPosiY + 45);
		mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 50, 50, 0, 0, 40, 40);
	}
}
 
void Bullet::Destroy()
{
}

BOOL Bullet::GetAct()
{
	return m_Act;
}

void Bullet::SetAct(BOOL value, Direction dir)
{
	m_Act = value;
	m_Direction = dir;
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
