#include "Map.h"
#pragma warning(disable : 4996)
#include "GameDirector.h"

void Map::Init(Character * pChar)
{
	m_pChar = pChar;
	m_Draw = true;
	GetBitmap()->LoadBitmapByPath("Resource/Map.bmp");
	mPosiX = 0;
	m_Cookie.clear();
	m_Cookie.reserve(60);
	for (int i = 0; i < 60; ++i)
	{
		Cookie temp;
		temp.Init(pChar);
		m_Cookie.push_back(temp);
	}
	for (int i = 0; i < GROUND_NUM; ++i)
	{
		m_Ground[i] = 1;
		m_BottomFork[i] = m_TopFork[i] = m_Awl[i] = 0;
		m_Collision[i] = 0;
	}
	m_Gate = false;
}

void Map::Init()
{
}

void Map::Update(float dt)
{
	mPosiX += 8;
	if (mPosiX >= 2560)
	{
		m_Draw = false;
	}

	if (m_Draw)
	{
		for (auto iter = m_Cookie.begin(); iter != m_Cookie.end(); ++iter)
		{
			iter->Update(dt);
		}

		RECT dest;
		int i = (mPosiX) / 128 + 1;
		RECT charRect = m_pChar->GetRect();
		if (mPosiX > 0 && i < 20)
		{
			if (m_Ground[i] == 0)
			{
				m_pChar->CheckGround(false);

				// 이미 떨어지는 중이 아니고 걷기나 슬라이드일때만 충돌 체크
				if (!m_pChar->CheckFall() && (m_pChar->GetMoveType() == WALK || m_pChar->GetMoveType() == SLIDE))
				{
					//Rectangle(hdc, ORI_TILE_SIZE * i - mPosiX, 510, ORI_TILE_SIZE * i - mPosiX + 128, 640);
					if (IntersectRect(&dest, &charRect, &GetRect(GROUND, i)))
					{
						if (dest.right - dest.left >= 80)
							m_pChar->SetMoveType(FALL);
						//TextOutA(hdc, 800, 30, "바닥낙하", 8);
					}
				}
			}
			else
			{
				m_pChar->CheckGround(true);
			}

			// 장애물 충돌처리
			if (m_BottomFork[i] == 1)
			{
				//Rectangle(hdc, ORI_TILE_SIZE * i - mPosiX + 35, 320, ORI_TILE_SIZE * i - mPosiX + 65, 320 + 192);
				if (IntersectRect(&dest, &charRect, &GetRect(BOTTOMFORK, i)) && m_Collision[i] == 0 && !m_pChar->CollisionDelay())
				{
					m_pChar->CheckCollision(true);
					m_pChar->MinusHP();
					m_Collision[i] = 1;
					//TextOutA(hdc, 800, 30, "포크충돌", 8);
				}
			}
			else if (m_Awl[i] == 1)
			{
				//Rectangle(hdc, ORI_TILE_SIZE * i - mPosiX + 55, 384, ORI_TILE_SIZE * i - mPosiX + 70, 384 + 128);
				if (IntersectRect(&dest, &charRect, &GetRect(AWL, i)) && m_Collision[i] == 0 && !m_pChar->CollisionDelay())
				{
					m_pChar->CheckCollision(true);
					m_pChar->MinusHP();
					m_Collision[i] = 1;
					//TextOutA(hdc, 800, 30, "송곳충돌", 8);
				}
			}
			else if (m_TopFork[i] == 1)
			{
				//Rectangle(hdc, ORI_TILE_SIZE * i - mPosiX, 0, ORI_TILE_SIZE * i - mPosiX + ORI_TILE_SIZE, 448);
				if (IntersectRect(&dest, &charRect, &GetRect(TOPFORK, i)) && m_Collision[i] == 0 && !m_pChar->CollisionDelay())
				{
					m_pChar->CheckCollision(true);
					m_pChar->MinusHP();
					m_Collision[i] = 1;
					//TextOutA(hdc, 800, 30, "탑포크충돌", 10);
				}
			}
		}

		if (m_Gate && mPosiX >= 1280)
		{
			GameDirector::GetGameDirector()->GetSceneManager()->reserveChangeScene("GameScene2");
		}
	}
}

void Map::Render(HDC hdc, float dt)
{
	if (m_Draw)
	{
		if (m_Gate)
		{
			for (int i = 0; i < GROUND_NUM; ++i)
			{
				int x = ORI_TILE_SIZE * i - mPosiX;
				if (m_Ground[i] == 1)
				{
					GetBitmap()->DrawBitmapByCropping(hdc, x, 512, ORI_TILE_SIZE, ORI_TILE_SIZE, 0, 192, 128, 128);
				}
			}
			GetBitmap()->DrawBitmapByCropping(hdc, 1280-mPosiX, 384, ORI_TILE_SIZE, ORI_TILE_SIZE, 0, 512, 128, 128);
		}
		else
		{
			for (int i = 0; i < GROUND_NUM; ++i)
			{
				int x = ORI_TILE_SIZE * i - mPosiX;
				if (m_Ground[i] == 1)
				{
					GetBitmap()->DrawBitmapByCropping(hdc, x, 512, ORI_TILE_SIZE, ORI_TILE_SIZE, 0, 192, 128, 128);
				}

				if (m_BottomFork[i] == 1)
				{
					GetBitmap()->DrawBitmapByCropping(hdc, x, 320, ORI_TILE_SIZE, 192, 0, 0, 128, 192);
				}
				else if (m_Awl[i] == 1)
				{
					GetBitmap()->DrawBitmapByCropping(hdc, x, 384, ORI_TILE_SIZE, ORI_TILE_SIZE, 0, 320, 128, 128);
				}
				else if (m_TopFork[i] == 1)
				{
					GetBitmap()->DrawBitmapByCropping(hdc, x, 0, ORI_TILE_SIZE, 448, 128, 32, 128, 480);
				}
			}
		}
		
		for (auto iter = m_Cookie.begin(); iter != m_Cookie.end(); ++iter)
		{
			iter->Render(hdc, dt);
		}
	}
}

void Map::Destroy()
{
	m_Cookie.clear();
}

BOOL Map::GetDraw()
{
	return m_Draw;
}

void Map::SetDraw(BOOL draw)
{
	// 맵 랜덤
 	//int r = 3;
	if (m_Draw = draw)
	{
		int r = rand() % 4;
		char filePath[64] = "Resource/Map/FirstMap";
		sprintf(filePath, "%s%d%s", filePath, r, ".txt");
		std::ifstream inputFile(filePath);

		// 맵 정보 가져오기
		for (int i = 0; i < GROUND_NUM; ++i)
		{
			inputFile >> m_Ground[i];
		}

		for (int i = 0; i < GROUND_NUM; ++i)
		{
			inputFile >> m_BottomFork[i];
		}

		for (int i = 0; i < GROUND_NUM; ++i)
		{
			inputFile >> m_Awl[i];
		}

		for (int i = 0; i < GROUND_NUM; ++i)
		{
			inputFile >> m_TopFork[i];
		}

		inputFile.close();

		// 동전 위치 설정
		int i = 0;
		int count = 0;
		for (auto iter = m_Cookie.begin(); iter != m_Cookie.end(); ++iter)
		{
			// mPosiX가 1280 뒤에서 시작하므로 + 1280해주기
			// count는 쿠키간의 간격
			if (m_TopFork[i] == 1)
			{
				iter->SetPosition(128 * i + count + 1280, 450);
			}
			else if (m_BottomFork[i] == 1)
			{
				if(count == 42)
					iter->SetPosition(128 * i + count + 1280, 180);
				else
					iter->SetPosition(128 * i + count + 1280, 220);
			}
			else if (m_Awl[i] == 1)
			{
				if (count == 42)
					iter->SetPosition(128 * i + count + 1280, 320);
				else
					iter->SetPosition(128 * i + count + 1280, 350);
			}
			else
			{
				// 땅만 있는경우 쿠키 위치
				if (i > 0 && m_BottomFork[i - 1] == 1)
					iter->SetPosition(128 * i + count + 1280, 252 + (32 + count));
				else if (i < 19 && m_BottomFork[i + 1] == 1)
					iter->SetPosition(128 * i + count + 1280, 400 - (32 + count));
				else
					iter->SetPosition(128 * i + count + 1280, 400);
			}

			count += 42;
			if (count == 126)
			{
				i++;
				count = 0;
			}
		}

		// 충돌확인 리셋(m_Collision으로 한번만 충돌처리 하게끔 하기)
		for (int i = 0; i < 20; ++i)
		{
			m_Collision[i] = 0;
		}
	}
}

void Map::SetGateDraw()
{
	for (int i = 0; i < 20; ++i)
	{
		m_Ground[i] = 1;
		m_BottomFork[i] = m_TopFork[i] = m_Awl[i] = 0;
	}
	m_Draw = true;
	m_Gate = true;
}

RECT Map::GetRect(Obstacle obstacle, int i)
{
	RECT rect;
	switch (obstacle)
	{
	case GROUND:
		rect = { ORI_TILE_SIZE * i - mPosiX + 10, 510, ORI_TILE_SIZE * i - mPosiX + 118, 640 };
		break;
	case BOTTOMFORK:
		rect = { ORI_TILE_SIZE * i - mPosiX + 35, 320, ORI_TILE_SIZE * i - mPosiX + 65, 512 };
		break;
	case TOPFORK:
		rect = { ORI_TILE_SIZE * i - mPosiX, 0, ORI_TILE_SIZE, 448 };
		break;
	case AWL:
		rect = { ORI_TILE_SIZE * i - mPosiX + 55, 384, ORI_TILE_SIZE * i - mPosiX + 70, 512 };
		break;
	}
	return rect;
}

Map::Map()
{
}


Map::~Map()
{
}
