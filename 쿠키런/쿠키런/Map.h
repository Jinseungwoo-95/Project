#pragma once
#include "Object.h"
#include "Cookie.h"

class Map : public Object
{
public:
	void Init(Character* pChar);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	BOOL GetDraw();
	void SetDraw(BOOL draw);
	void SetGateDraw();

	RECT GetRect(Obstacle obstacle, int i);

private:
	Character*		m_pChar;
	vector<Cookie>	m_Cookie;
	int				m_Collision[GROUND_NUM];

	BOOL	m_Gate;
	BOOL	m_Draw;
	int		m_Ground[GROUND_NUM];
	int		m_BottomFork[GROUND_NUM];	// 바닥 포크
	int		m_TopFork[GROUND_NUM];
	int		m_Awl[GROUND_NUM];	// 송곳

public:
	Map();
	~Map();
};

