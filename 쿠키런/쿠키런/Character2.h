#pragma once
#include "Object.h"
#include "Bullet.h"
//#include "Boss.h"

class Character2 : public Object
{
private:
	list<Bullet>	m_Bullet;
	DWORD	m_BulletTime;

	int		m_HP;
	float	m_Time;
	int		m_JumpY;	// 점프 한 위치
	DWORD	m_JTime;	// 더블 점프 간격 시간용
	int		m_JumpCount;

	BOOL	m_GameStart;

	MoveType2	m_MoveType;
	Direction	m_Direction;
	DWORD	m_SpriteAnimNow;
	DWORD	m_SpriteAnimStart;
	DWORD	m_SpriteAnimEnd;
	DWORD	m_aniCount;

	BOOL	m_KeyCheck;
	Bitmap	m_NumBitmap;

public:
	void Init(Boss* pBoss);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();
	RECT	GetRect();
	void	MinusHP(int value);

	Character2();
	~Character2();
};

