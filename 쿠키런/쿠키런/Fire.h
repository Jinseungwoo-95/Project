#pragma once
#include "Object.h"

class Character2;
class Fire : public Object
{
private:
	Character2* m_pChar;
	BOOL	m_Act;
	BOOL	m_Collision;
	DWORD	m_SpriteTime;
	Direction m_Direction;
public:
	void Init(Character2* pChar);
	BOOL GetAct();
	void SetAct(BOOL value);
	void SetDirection(Direction value);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	Fire();
	~Fire();
};

