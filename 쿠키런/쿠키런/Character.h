#pragma once
#include "Object.h"

class GameScene;
class Character : public Object
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	RECT		GetRect();
	MoveType	GetMoveType();
	void		SetMoveType(MoveType type);
	BOOL		CheckFall();
	void		CheckGround(BOOL value);
	void		CheckCollision(BOOL value);
	void		MinusHP();
	BOOL		CollisionDelay();
private:
	int		m_aniNum;
	DWORD	m_aniCount;

	float	m_Time;
	int		m_JumpY;	// 점프 한 위치
	DWORD	m_JTime;	// 더블 점프 간격 시간용
	int		m_JumpCount;

	BOOL	m_Fall;
	BOOL	m_CheckGround;

	MoveType	m_MoveType;

	BOOL	m_Collision;	// 장애물 충돌
	DWORD	m_CollisionTime;	// 충돌 후 일정시간 무적
	BOOL	m_CollisionDelay;
	int	m_HP;
	Bitmap	m_NumBitmap;
public:
	Character();
	~Character();
};

