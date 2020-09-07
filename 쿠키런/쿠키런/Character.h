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
	int		m_JumpY;	// ���� �� ��ġ
	DWORD	m_JTime;	// ���� ���� ���� �ð���
	int		m_JumpCount;

	BOOL	m_Fall;
	BOOL	m_CheckGround;

	MoveType	m_MoveType;

	BOOL	m_Collision;	// ��ֹ� �浹
	DWORD	m_CollisionTime;	// �浹 �� �����ð� ����
	BOOL	m_CollisionDelay;
	int	m_HP;
	Bitmap	m_NumBitmap;
public:
	Character();
	~Character();
};

