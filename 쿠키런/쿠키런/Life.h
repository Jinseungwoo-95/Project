#pragma once
#include "Object.h"
#include "Character.h"

class Life : public Object
{
private:
	BOOL	m_Act;
	BOOL	m_Collision;
	Character* m_pChar;

public:
	void Init(Character* pChar);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	void	SetPosition(int x, int y);
	BOOL	GetAct();
};

