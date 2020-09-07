#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "Character2.h"
#include "Boss.h"

class GameScene2 : public Scene
{
private:
	Character2	m_Char;
	Boss		m_Boss;
	BackGround	m_BackGround;
	BackGround	m_Ground[10];

public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	GameScene2();
	~GameScene2();


};

