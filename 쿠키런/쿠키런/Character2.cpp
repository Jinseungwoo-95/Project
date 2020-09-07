#include "Character2.h"

#pragma warning(disable:4996)

// WALK		0~3 / 6~9
// JUMP		0~2 / 6~8
// DJUMP	0~5 / 6~11
// SLIDE	0	/ 6
// HIT		0	/ 6

void Character2::Init(Boss * pBoss)
{
	for (int i = 0; i < 10; ++i)
	{
		Bullet temp;
		temp.Init(pBoss);
		m_Bullet.push_back(temp);
	}
	m_BulletTime = 0;

	mPosiX = -200;
	mPosiY = 352;
	m_GameStart = false;

	m_HP = 10;

	m_Time = 0;
	m_JumpY = 0;
	m_JTime = 0;
	m_JumpCount = 0;

	m_MoveType = MoveType2::WALK;
	m_Direction = RIGHT;

	m_SpriteAnimNow = 0;
	m_SpriteAnimStart = 0;
	m_SpriteAnimEnd = 3;

	m_aniCount = 0;
	m_KeyCheck = false;
	mBitmap.LoadBitmapByPath("Resource/Character2.bmp");
	m_NumBitmap.LoadBitmapByPath("Resource/Number.bmp");
}

void Character2::Init()
{
}

void Character2::Update(float dt)
{
	// 처음 케릭 등장
	if (!m_GameStart)
	{
		mPosiX += 5;
		if (m_aniCount + 100 < GetTickCount())
		{
			m_aniCount = GetTickCount();
			m_SpriteAnimNow = (++m_SpriteAnimNow > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteAnimNow;
		}
		if (mPosiX >= 100)
		{
			m_GameStart = true;
		}
	}
	else
	{
		m_KeyCheck = false;

		// 점프가 아닐때는 슬라이드 가능
		if (m_MoveType != MoveType2::JUMP && m_MoveType != MoveType2::DJUMP)
		{
			if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				if (m_Direction == RIGHT)
					m_SpriteAnimNow = 0;
				else
					m_SpriteAnimNow = 6;
				m_MoveType = MoveType2::SLIDE;
				m_KeyCheck = true;
			}
		}

		// 불렛 생성
		if (GetAsyncKeyState('A') & 0x8000 && m_BulletTime + 500 < GetTickCount())
		{
			m_BulletTime = GetTickCount();
			for (auto iter = m_Bullet.begin(); iter != m_Bullet.end(); ++iter)
			{
				if (!iter->GetAct())
				{
					iter->SetAct(true, m_Direction);
					if (m_Direction == RIGHT)
					{
						iter->SetX(mPosiX + 50);
						iter->SetY(mPosiY + 100);
					}
					else
					{
						iter->SetX(mPosiX);
						iter->SetY(mPosiY + 100);
					}
					--g_Bullet;
					break;
				}
			}
		}

		// 불렛 업데이트
		for (auto iter = m_Bullet.begin(); iter != m_Bullet.end(); ++iter)
		{
			iter->Update(dt);
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			// 1단 점프
			if (m_JumpCount == 0)
			{
				m_Time = 0.f;
				m_JumpY = mPosiY;
				m_JTime = GetTickCount();
				m_MoveType = MoveType2::JUMP;
				m_JumpCount = 1;
				m_aniCount = GetTickCount();
				if (m_Direction == RIGHT)
				{
					m_SpriteAnimStart = 0;
					m_SpriteAnimEnd = 2;
				}
				else
				{
					m_SpriteAnimStart = 6;
					m_SpriteAnimEnd = 8;
				}
				m_SpriteAnimNow = m_SpriteAnimStart;
			}
			// 2단 점프
			else if (m_JTime + 200 < GetTickCount() && m_JumpCount == 1)
			{
				m_Time = 0.f;
				m_JumpY = mPosiY;
				m_MoveType = MoveType2::DJUMP;
				m_JumpCount = 2;
				m_aniCount = GetTickCount();
				if (m_Direction == RIGHT)
				{
					m_SpriteAnimStart = 0;
					m_SpriteAnimEnd = 5;
				}
				else
				{
					m_SpriteAnimStart = 6;
					m_SpriteAnimEnd = 11;
				}
				m_SpriteAnimNow = m_SpriteAnimStart;
			}
		}

		if (m_MoveType == MoveType2::DJUMP || m_MoveType == MoveType2::JUMP)
		{
			m_Time += 0.25f;
			mPosiY = m_JumpY - (55 * m_Time - 0.5 * 9.81 * m_Time * m_Time);

			if (mPosiY >= 352)
			{
				mPosiY = 352;
				m_MoveType = MoveType2::NOMAL;
				m_SpriteAnimNow = 0;
				m_JumpCount = 0;
			}
			if (m_aniCount + 100 < GetTickCount())
			{
				m_aniCount = GetTickCount();
				if (m_SpriteAnimNow < m_SpriteAnimEnd)
					m_SpriteAnimNow++;
				//m_SpriteAnimNow = (++m_SpriteAnimNow > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteAnimNow;
			}
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_KeyCheck = true;
			if (m_Direction != RIGHT)
			{
				m_Direction = RIGHT;
				m_SpriteAnimStart = 0;
				m_SpriteAnimNow = m_SpriteAnimStart;

				switch (m_MoveType)
				{
				case MoveType2::WALK:
					m_SpriteAnimEnd = 3;
					break;
				case MoveType2::JUMP:
					m_SpriteAnimEnd = 2;
					break;
				case MoveType2::DJUMP:
					m_SpriteAnimEnd = 5;
					break;
				case MoveType2::SLIDE:
					m_SpriteAnimEnd = 0;
					break;
				case MoveType2::NOMAL:
					m_SpriteAnimEnd = 0;
					break;
				}

			}

			if (m_MoveType != MoveType2::JUMP && m_MoveType != MoveType2::DJUMP && m_MoveType != MoveType2::WALK)
			{
				m_MoveType = MoveType2::WALK;
				m_aniCount = GetTickCount();
				m_SpriteAnimStart = 0;
				m_SpriteAnimNow = m_SpriteAnimStart;
				m_SpriteAnimEnd = 3;
			}
			else if (m_aniCount + 100 < GetTickCount())
			{
				m_aniCount = GetTickCount();
				m_SpriteAnimNow = (++m_SpriteAnimNow > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteAnimNow;
			}

			if (mPosiX <= 1147)
			{
				mPosiX += 5;
			}

		}

		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_KeyCheck = true;
			if (m_Direction != LEFT)
			{
				m_Direction = LEFT;
				m_SpriteAnimStart = 6;
				m_SpriteAnimNow = m_SpriteAnimStart;
				switch (m_MoveType)
				{
				case MoveType2::WALK:
					m_SpriteAnimEnd = 9;
					break;
				case MoveType2::JUMP:
					m_SpriteAnimEnd = 8;
					break;
				case MoveType2::DJUMP:
					m_SpriteAnimEnd = 11;
					break;
				case MoveType2::SLIDE:
					m_SpriteAnimEnd = 6;
					break;
				case MoveType2::NOMAL:
					m_SpriteAnimEnd = 6;
					break;
				}
			}

			if (m_MoveType != MoveType2::JUMP && m_MoveType != MoveType2::DJUMP && m_MoveType != MoveType2::WALK)
			{
				m_MoveType = MoveType2::WALK;
				m_aniCount = GetTickCount();
				m_SpriteAnimStart = 6;
				m_SpriteAnimNow = m_SpriteAnimStart;
				m_SpriteAnimEnd = 9;
			}
			else if (m_aniCount + 100 < GetTickCount())
			{
				m_aniCount = GetTickCount();
				m_SpriteAnimNow = (++m_SpriteAnimNow > m_SpriteAnimEnd) ? m_SpriteAnimStart : m_SpriteAnimNow;
			}

			if (mPosiX >= 5)
			{
				mPosiX -= 5;
			}
		}

		// 다운, 레프트, 라이트키가 안눌렸을 경우 노멀로 바꾸기
		if (!m_KeyCheck && m_MoveType != MoveType2::JUMP && m_MoveType != MoveType2::DJUMP)
		{
			if (m_Direction == RIGHT)
				m_SpriteAnimNow = 0;
			else
				m_SpriteAnimNow = 6;
			m_MoveType = MoveType2::NOMAL;
		}

		// 생명이 0이거나 남은 불렛이 0일 경우
		if (m_HP <= 0 || g_Bullet <= 0)
		{
			GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("GameOverScene");
		}
	}
}

void Character2::Render(HDC hdc, float dt)
{
	/*char a[256];
	sprintf(a, "char HP : %d", m_HP);
	TextOutA(hdc, 500, 300, a, strlen(a));

	sprintf(a, "X : %d, Y : %d", mPosiX, mPosiY);
	TextOutA(hdc, mPosiX, mPosiY, a, strlen(a));*/
	
	char hp[4];
	char bullet[128];

	itoa(m_HP, hp, 10);
	itoa(g_Bullet, bullet, 10);

	int i = 0;

	while (hp[i] != NULL)
	{
		m_NumBitmap.DrawBitmapByCropping(hdc, 100 + (30 * i), 15, 35, 50, 35 * ((int)hp[i] -48), 0, 35, 50);
		++i;
	}

	i = 0;
	while (bullet[i] != NULL)
	{
		m_NumBitmap.DrawBitmapByCropping(hdc, 100 + (30 * i), 95, 35, 50, 35 * ((int)bullet[i] - 48), 0, 35, 50);
		++i;
	}

	if (m_MoveType == MoveType2::SLIDE)
	{
		//Rectangle(hdc, mPosiX + 15, mPosiY + 110, mPosiX + 135, mPosiY + 160);
		mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 160, 160, 128 * m_SpriteAnimNow, 192 * (int)m_MoveType, 192, 192);
	}
	else
	{
		//Rectangle(hdc, mPosiX + 25, mPosiY + 70, mPosiX + 80, mPosiY + 160);
		mBitmap.DrawBitmapByCropping(hdc, mPosiX, mPosiY, 96, 160, 128 * m_SpriteAnimNow, 192 * (int)m_MoveType, 128, 192);
	}

	for (auto iter = m_Bullet.begin(); iter != m_Bullet.end(); ++iter)
	{
		iter->Render(hdc, dt);
	}
}

void Character2::Destroy()
{
	for (auto iter = m_Bullet.begin(); iter != m_Bullet.end(); ++iter)
	{
		iter->Destroy();
	}
}

RECT Character2::GetRect()
{
	RECT rect;
	if (m_MoveType == MoveType2::SLIDE)
		rect = { mPosiX + 15, mPosiY + 110, mPosiX + 135, mPosiY + 160 };
	else
		rect = { mPosiX + 25, mPosiY + 70, mPosiX + 80, mPosiY + 160 };

	return rect;
}

void Character2::MinusHP(int value)
{
	m_HP -= value;
}

Character2::Character2()
{
}


Character2::~Character2()
{
}
