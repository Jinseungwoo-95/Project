#pragma once
#include "Object.h"
#include "Bitmap.h"
#include "GameDirector.h"
#include "Fire.h"
#include "Fire2.h"

class Character2;
class Boss : public Object
{
private:
	int	m_HP;
	BossType m_Type;

	DWORD	m_SpriteAnimNow;
	DWORD	m_SpriteAnimStart;
	DWORD	m_SpriteAnimEnd;
	DWORD	m_aniCount;

	DWORD	m_RushCount;
	int		m_RushSpeed;

	vector<Fire> m_Fire;
	list<Fire2> m_Fire2;
	DWORD	m_FireTime;	// 수직	파이어
	DWORD	m_FireTime2;	// 대각선 파이어
	Character2* m_pChar;
	BOOL	m_CollisionTime;
	Bitmap	m_NumBitmap;

public:
	void Init(Character2* pChar);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	void SetType(BossType value);
	BossType GetType();
	void MinusHP(DWORD value);

	RECT GetRect();
	Boss();
	~Boss();
};

