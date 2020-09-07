#pragma once
#include "Object.h"
#include "Boss.h"

class Bullet : public Object
{
private:
	BOOL	m_Act;
	Boss*	m_pBoss;
	Direction m_Direction;
public:
	void Init(Boss* pBoss);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	BOOL GetAct();
	void SetAct(BOOL value, Direction dir);

	Bullet();
	~Bullet();
};

