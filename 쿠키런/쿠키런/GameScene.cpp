#include "GameScene.h"
#pragma warning(disable : 4996)
#include "GameDirector.h"

void GameScene::Init()
{
	m_EndCount = 0;

	m_Char.Init();
	m_Map.Init(&m_Char);
	m_Map2.Init(&m_Char);

	m_Map2.SetDraw(false);
	// 백그라운드
	RECT rc = { 0,0,1280,670 };
	m_BackGround.Init(const_cast<char *>("background.bmp"), rc);
}

void GameScene::Update(float dt)
{
	m_BackGround.Update(dt);

	if (m_Map.GetDraw())
	{
		m_Map.Update(dt);
		if (!m_Map2.GetDraw() && m_Map.GetX() >= 1280)
		{
			m_Map2.SetDraw(true);
			m_Map2.SetX(-m_Map.GetX());
			++m_EndCount;
		}

	}
	if (m_Map2.GetDraw())
	{
		m_Map2.Update(dt);
		if (!m_Map.GetDraw() && m_Map2.GetX() >= 1280)
		{
			if (m_EndCount >= 9)
			{
				m_Map.SetGateDraw();
			}
			else
			{
				m_Map.SetDraw(true);
			}
			m_Map.SetX(-m_Map2.GetX());
			++m_EndCount;
		}
	}

	m_Char.Update(dt);
}

void GameScene::Render(HDC hdc, float dt)
{
	m_BackGround.Render(hdc, dt);

	/*char text[256];
	sprintf(text, "X : %d, X2 : %d", m_Map.GetX(), m_Map2.GetX());
	TextOutA(hdc, 200, 30, text, strlen(text));

	sprintf(text, "m_EndCount : %d", m_EndCount);
	TextOutA(hdc, 600, 30, text, strlen(text));*/

	m_Map.Render(hdc, dt);
	m_Map2.Render(hdc, dt);
	m_Char.Render(hdc, dt);
}

void GameScene::Destroy()
{
	m_BackGround.Destroy();
	m_Map.Destroy();
	m_Map2.Destroy();
	m_Char.Destroy();
}

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}
