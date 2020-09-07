#pragma once
#include "Object.h"
#include "Character.h"

class Money : public Object
{
private:
	BOOL	m_Act;
	Character*	m_pChar;
	int		m_AniNum;
	DWORD	m_AniCount;
	BOOL	m_Collision;

public:
	void Init(Character* pChar);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	void	SetPosition(int x, int y);
	BOOL	GetAct();

	Money();
	~Money();


};

