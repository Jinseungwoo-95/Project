#include "Character.h"
#include "GameScene.h"
#include "GameDirector.h"
#pragma warning(disable : 4996)

void Character::Init()
{
	m_aniNum = 0;
	m_aniCount = 0;
	m_Time = 0;
	m_JumpCount = 0;
	m_JumpY = 0;
	m_JTime = 0;
	m_Fall = false;
	m_MoveType = WALK;
	m_HP = 5;
	mPosiX = 50;
	mPosiY = 320;
	m_Collision = false;
	m_CollisionDelay = false;
	GetBitmap()->LoadBitmapByPath("Resource/Character.bmp");
	m_NumBitmap.LoadBitmapByPath("Resource/Number.bmp");
	g_Bullet = 0;
}

void Character::Update(float dt)
{
	if (m_MoveType == WALK || m_MoveType == SLIDE)
	{
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_MoveType = SLIDE;
		}
		else
		{
			m_MoveType = WALK;
		}
	}
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		// 1단 점프
		if (m_JumpCount == 0)
		{
			m_Time = 0.f;
			m_JumpY = mPosiY;
			m_JTime = GetTickCount();
			m_MoveType = JUMP;
			m_aniNum = 0;
			m_JumpCount = 1;
		}
		// 2단 점프
		else if (m_JTime + 200 < GetTickCount() && m_JumpCount == 1)
		{
			m_Time = 0.f;
			m_JumpY = mPosiY;
			m_MoveType = DJUMP;
			m_aniNum = 0;
			m_JumpCount = 2;
		}
	}
	
	if (m_MoveType == DJUMP || m_MoveType == JUMP)
	{
		m_Time += 0.25f;
		mPosiY = m_JumpY - (55 * m_Time - 0.5 * 9.81 *m_Time*m_Time);
		if (mPosiY < 320) m_Fall = false;
		if (mPosiY > 340) m_Fall = true;

		if (mPosiY >= 320 && !m_Fall && m_CheckGround) // 떨어지는중이 아니고 땅이 있을경우
		{
			mPosiY = 320;
			m_MoveType = WALK;
			m_JumpCount = 0;
		}
	}
	else if (m_MoveType == FALL)
	{
		m_Time += 0.3f;

		mPosiY =  320 + 0.5 * 9.81 * m_Time * m_Time;
	}

	if (m_aniCount + 100 < GetTickCount())
	{
		m_aniCount = GetTickCount();
		switch (m_MoveType)
		{
		case WALK: case FALL:
			m_aniNum = ++m_aniNum > 3 ? 0 : m_aniNum;
			break;
		case JUMP:
			if (m_aniNum < 2)
				++m_aniNum;
			break;
		case DJUMP:
			if (m_aniNum < 5)
				++m_aniNum;
			break;
		case SLIDE:
			m_aniNum = 0;
			break;
		}
	}

	// 충돌 애니메이션 종료
	if (m_Collision && m_CollisionTime + 100 < GetTickCount())
	{
		m_Collision = false;
	}

	// 충돌 후 3초간 무적
	if (m_CollisionTime + 3000 < GetTickCount())
	{
		m_CollisionDelay = false;
	}

	if (mPosiY > 700 || m_HP <= 0)
	{
		GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("GameOverScene");
	}
}

void Character::Render(HDC hdc, float dt)
{
//#define VIEW_CHARINFO	// 이거 주석하면 ifdef 실행안됨.

#ifdef VIEW_CHARINFO
	if (m_MoveType == SLIDE)
		// 슬라이드 충돌
		Rectangle(hdc, mPosiX, mPosiY + 128, mPosiX + 168, mPosiY + 192);
	else
		// 워크 충돌
		Rectangle(hdc, mPosiX + 18, mPosiY + 64, mPosiX + 110, mPosiY + 192);
	 
	char text[256];
	sprintf(text, "L : %d, T : %d", mPosiX, mPosiY);
	TextOutA(hdc, mPosiX, mPosiY - 50, text, strlen(text));

	sprintf(text, "R : %d, B : %d", mPosiX + 128, mPosiY + 192);
	TextOutA(hdc, mPosiX, mPosiY - 30, text, strlen(text));

	sprintf(text, "jumpcount : %d", m_JumpCount);
	TextOutA(hdc, 400, 30, text, strlen(text));

	sprintf(text, "Time : %f", m_Time);
	TextOutA(hdc, 400, 50, text, strlen(text));

	sprintf(text, "Movetype : %d", (int)m_MoveType);
	TextOutA(hdc, 400, 70, text, strlen(text));
#endif
	char hp[2];
	char bullet[128];

	itoa(m_HP, hp, 10);
	itoa(g_Bullet, bullet, 10);

	m_NumBitmap.DrawBitmapByCropping(hdc, 100, 15, 35, 50, 35 * m_HP, 0, 35, 50);

	int i = 0;
	while (bullet[i] != NULL)
	{
		m_NumBitmap.DrawBitmapByCropping(hdc, 100 + (30 * i), 95, 35, 50, 35 * ((int)bullet[i] - 48), 0, 35, 50);
		++i;
	}

	if (m_Collision)
	{
		GetBitmap()->DrawBitmapByCropping(hdc, mPosiX, mPosiY, ORI_TILE_SIZE, 192, 0, 768, 128, 192, m_CollisionDelay);
	}
	else if (m_MoveType == SLIDE)
		GetBitmap()->DrawBitmapByCropping(hdc, mPosiX, mPosiY, 192, 192, ORI_TILE_SIZE * m_aniNum, 192 * m_MoveType, ORI_TILE_SIZE + 64, 192, m_CollisionDelay);
	else if (m_MoveType == FALL)
		GetBitmap()->DrawBitmapByCropping(hdc, mPosiX, mPosiY, ORI_TILE_SIZE, 192, ORI_TILE_SIZE * m_aniNum, 0, ORI_TILE_SIZE, 192, m_CollisionDelay);
	else
		GetBitmap()->DrawBitmapByCropping(hdc, mPosiX, mPosiY, ORI_TILE_SIZE, 192, ORI_TILE_SIZE * m_aniNum, 192 * m_MoveType, ORI_TILE_SIZE, 192, m_CollisionDelay);
}

void Character::Destroy()
{
}

RECT Character::GetRect()
{
	RECT rect;
	if(m_MoveType == SLIDE)
		rect = { mPosiX, mPosiY + 128, mPosiX + 168 , mPosiY + 192 };
	else
		rect = { mPosiX + 25, mPosiY + 64, mPosiX + 110 , mPosiY + 192 };

	return rect;
}

MoveType Character::GetMoveType()
{
	return m_MoveType;
}

void Character::SetMoveType(MoveType type)
{
	if (type == FALL)
	{
		m_Time = 0.f;
		m_MoveType = type;
		m_Fall = true;
	}
}

BOOL Character::CheckFall()
{
	return m_Fall;
}

void Character::CheckGround(BOOL value)
{
	m_CheckGround = value;
}

void Character::CheckCollision(BOOL value)
{
	m_Collision = value;
	m_CollisionDelay = true;
	m_CollisionTime = GetTickCount();
}

void Character::MinusHP()
{
	--m_HP;
}

BOOL Character::CollisionDelay()
{
	return m_CollisionDelay;
}

Character::Character()
{
}


Character::~Character()
{
}
