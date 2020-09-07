#include "GameScene2.h"



void GameScene2::Init()
{
	RECT rc = { 0,0,1280,670 };
	m_BackGround.Init(const_cast<char *>("background.bmp"), rc);

	for (int i = 0; i < 10; ++i)
	{
		rc = { 128 * i, 512, 128 * (i + 1), 640 };
		m_Ground[i].Init(const_cast<char *>("Ground.bmp"), rc);
	}
	m_Char.Init(&m_Boss);
	m_Boss.Init(&m_Char);
}

void GameScene2::Update(float dt)
{
	/*m_BackGround.Update(dt);
	for (int i = 0; i < 10; ++i)
	{
		m_Ground[i].Update(dt);
	}*/
	m_Char.Update(dt);
	m_Boss.Update(dt);
}

void GameScene2::Render(HDC hdc, float dt)
{
	m_BackGround.Render(hdc, dt);
	for (int i = 0; i < 10; ++i)
	{
		m_Ground[i].Render(hdc, dt);
	}
	m_Char.Render(hdc, dt);
	m_Boss.Render(hdc, dt);
}

void GameScene2::Destroy()
{
	m_BackGround.Destroy();
	for (int i = 0; i < 10; ++i)
	{
		m_Ground[i].Destroy();
	}
	m_Char.Destroy();
	m_Boss.Destroy();
}

GameScene2::GameScene2()
{
}


GameScene2::~GameScene2()
{
}
