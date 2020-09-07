#pragma once
#include "Scene.h"
#include "Character.h"
#include "BackGround.h"
#include "Map.h"

class GameScene : public Scene
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();
private:
	Map			m_Map;
	Map			m_Map2;
	BackGround	m_BackGround;
	Character	m_Char;
	int	m_EndCount;
public:
	GameScene();
	~GameScene();
};

