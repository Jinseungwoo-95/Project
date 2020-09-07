#pragma once
#include "Object.h"

class Character2;

class Fire2 : public Object
{
private:
	Character2* m_pChar;
	BOOL	m_Remove;
public:
	void Init(Character2* pChar);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	BOOL GetRemove();

	Fire2();
	~Fire2();
};

