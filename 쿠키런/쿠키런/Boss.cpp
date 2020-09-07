
#include "Boss.h"
#include "Character2.h"

#pragma warning(disable:4996)

void Boss::Init(Character2 * pChar)
{
	mPosiX = 1100;
	mPosiY = 320;
	m_HP = 150;

	m_Type = IDLE;
	m_SpriteAnimNow = 0;
	m_SpriteAnimStart = 0;
	m_SpriteAnimEnd = 0;

	m_CollisionTime = 0;
	m_aniCount = GetTickCount();
	m_pChar = pChar;

	m_RushCount = 0;
	m_RushSpeed = 10;

	mBitmap.LoadBitmapByPath("Resource/Boss.bmp");
	m_NumBitmap.LoadBitmapByPath("Resource/Number.bmp");
	m_FireTime = 0;
	m_FireTime2 = 0;
	m_Fire.reserve(20);
	for (int i = 0; i < 20; ++i)
	{
		Fire temp;
		temp.Init(pChar);
		m_Fire.push_back(temp);
	}
}

void Boss::Init()
{
}

void Boss::Update(float dt)
{
	// 애니메이션 변경
	switch (m_Type)
	{
	case IDLE:
		if (m_aniCount + 2000 < GetTickCount())
		{
			m_aniCount = GetTickCount();
			SetType(ATTACK2);
		}
		break;
	case ATTACK1:
		break;
	case ATTACK2:
		if (m_aniCount + 300 < GetTickCount())
		{
			m_aniCount = GetTickCount();
			m_FireTime2 = GetTickCount();
			for (auto iter = m_Fire.begin(); iter != m_Fire.end(); ++iter)
			{
				if (!iter->GetAct())
				{
					iter->SetAct(true);
					iter->SetDirection((Direction)(rand() % 2 + 1));
					iter->SetX(rand() % 1242);
					iter->SetY(5);
					break;
				}
			}
			if (m_SpriteAnimNow < m_SpriteAnimEnd)
				++m_SpriteAnimNow;

			if (m_HP <= 100)
				SetType(CHANGE);
		}
		break;
	case CHANGE:
		if (m_aniCount + 300 < GetTickCount())
		{
			m_aniCount = GetTickCount();
			if (m_SpriteAnimNow < m_SpriteAnimEnd)
				++m_SpriteAnimNow;
			else
				SetType(RUSH);
		}
		break;
	case RUSH:
		if (m_SpriteAnimNow < m_SpriteAnimEnd)
		{
			if (m_SpriteAnimNow == 4)
			{
				mPosiX -= m_RushSpeed;
				if (mPosiX <= -100)
				{
					if (m_HP <= 75)
					{
						mPosiX = 1100;
						++m_SpriteAnimNow;
					}
					else
					{
						mPosiX = 1400;
						++m_RushSpeed;
					}
				}
			}
			else
			{
				if (m_aniCount + 300 < GetTickCount())
				{
					m_aniCount = GetTickCount();
					++m_SpriteAnimNow;
				}
			}
		}
		else
		{
			SetType(FIRE);
		}
		break;
	case FIRE:
		if (m_aniCount + 300 < GetTickCount())
		{
			m_aniCount = GetTickCount();
			if (m_SpriteAnimNow == m_SpriteAnimEnd)
			{
				int r = rand() % 5 + 2;
				m_SpriteAnimNow = m_SpriteAnimStart;
				for (int i = 0; i < 9; ++i)
				{
					if (i == r || i == r + 1 || i == r + 2)
						continue;
					Fire2 temp;
					temp.Init(m_pChar);
					temp.SetX(1280);
					temp.SetY(57 * i);
					m_Fire2.push_back(temp);
				}
			}
			else
			{
				++m_SpriteAnimNow;
			}
		}
		if (m_HP <= 0)
		{
			SetType(DIE);
		}
		break;
	case DIE:
		if (m_aniCount + 500 < GetTickCount())
		{
			m_aniCount = GetTickCount();
			if (m_SpriteAnimNow < m_SpriteAnimEnd)
			{
				++m_SpriteAnimNow;
			}
			else
				GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("ClearScene");
		}
		break;
	}

	// 파이어 생성
	if (m_Type != FIRE && m_Type != DIE)
	{
		if (m_FireTime + 500 < GetTickCount())
		{
			m_FireTime = GetTickCount();
			for (auto iter = m_Fire.begin(); iter != m_Fire.end(); ++iter)
			{
				if (!iter->GetAct())
				{
					iter->SetAct(true);
					iter->SetDirection(VERTICAL);
					RECT charRect = m_pChar->GetRect();
					int x = rand() % 1242;
					while (true)
					{
						if (charRect.left - 30 <= x && charRect.right + 30 >= x)
						{
							x = rand() % 1242;
						}
						else
						{
							break;
						}
					}
					iter->SetX(x);
					iter->SetY(5);
					break;
				}
			}
		}
	}

	for (auto iter = m_Fire.begin(); iter != m_Fire.end(); ++iter)
	{
		iter->Update(dt);
	}

	for (auto iter = m_Fire2.begin(); iter != m_Fire2.end();)
	{
		if (iter->GetRemove())
		{
			m_Fire2.erase(iter++);
		}
		else
		{
			iter->Update(dt);
			iter++;
		}
	}

	// 캐릭터 충돌 체크
	RECT dest;
	if (IntersectRect(&dest, &GetRect(), &m_pChar->GetRect()) && m_CollisionTime + 1000 < GetTickCount())
	{
		m_CollisionTime = GetTickCount();
		m_pChar->MinusHP(3);
	}
}

void Boss::Render(HDC hdc, float dt)
{
	/*if (m_Type == RUSH && (m_SpriteAnimNow == 4 || m_SpriteAnimNow == 5))
	{
		Rectangle(hdc, mPosiX + 30, mPosiY + 60, mPosiX + 162, mPosiY + 172);
	}
	else
	{
		Rectangle(hdc, mPosiX + 55, mPosiY + 20, mPosiX + 140, mPosiY + 192);
	}*/
	char hp[4];
	itoa(m_HP, hp, 10);
	for (int i = 0; hp[i] != NULL; ++i)
	{
		m_NumBitmap.DrawBitmapByCropping(hdc, 1150 + (30 * i), 15, 35, 50, 35 * ((int)hp[i] - 48), 0, 35, 50);
	}
	mBitmap.DrawBitmapByCropping(hdc, 1100, 15, 35, 50, 0, 0, 192, 192);

	mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 192, 192, 192 * m_SpriteAnimNow, 192 * m_Type, 192, 192);

	for (auto iter = m_Fire.begin(); iter != m_Fire.end(); ++iter)
	{
		iter->Render(hdc, dt);
	}
	for (auto iter = m_Fire2.begin(); iter != m_Fire2.end(); ++iter)
	{
		iter->Render(hdc, dt);
	}
}

void Boss::Destroy()
{
	for (auto iter = m_Fire.begin(); iter != m_Fire.end(); ++iter)
	{
		iter->Destroy();
	}
}

void Boss::SetType(BossType value)
{
	m_Type = value;
	m_SpriteAnimNow = 0;
	m_SpriteAnimStart = 0;
	switch (m_Type)
	{
	case ATTACK1:
		m_SpriteAnimEnd = 0;
		break;
	case ATTACK2:
		m_SpriteAnimEnd = 2;
		break;
	case CHANGE:
		m_SpriteAnimEnd = 7;
		break;
	case RUSH:
		m_SpriteAnimEnd = 6;
		break;
	case FIRE:
		m_SpriteAnimEnd = 4;
		break;
	case DIE:
		m_SpriteAnimEnd = 6;
		break;
	}
}

BossType Boss::GetType()
{
	return m_Type;
}

void Boss::MinusHP(DWORD value)
{
	m_HP -= value;
}

RECT Boss::GetRect()
{
	RECT rect;
	if (m_Type == RUSH && (m_SpriteAnimNow == 4 || m_SpriteAnimNow == 5))
	{
		rect = { mPosiX + 30, mPosiY + 60, mPosiX + 162, mPosiY + 172 };
	}
	else
	{
		rect = { mPosiX + 55, mPosiY + 20, mPosiX + 140, mPosiY + 192 };
	}
	return rect;
}

Boss::Boss()
{
}


Boss::~Boss()
{
}
