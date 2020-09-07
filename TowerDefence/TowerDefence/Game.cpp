#include "Game.h"
#include "DoubleBuffer.h"
#include "KeyManager.h"
#include "CollisionManager.h"
#include "StateManager.h"
#pragma warning(disable : 4996)

void Game::Initialize()
{
	srand(GetTickCount());

	map = new Map;
	map->Initialize();

	player = static_cast<Player*>(ObjFactory::GetInst()->CreateObj(PLAYER));

	for (int i = 0; i < TowerCount; ++i)
	{
		tower[i] = static_cast<Tower*>(ObjFactory::GetInst()->CreateObj(TOWER));
	}

	for (int i = 0; i < BulletCount; ++i)
	{
		bullets[i] = static_cast<Bullet*>(ObjFactory::GetInst()->CreateObj(BULLET));
	}

	for (int i = 0; i < EnemyCount; ++i)
	{
		enemies[i] = static_cast<Enemy*>(ObjFactory::GetInst()->CreateObj(ENEMY));
	}

	srand((unsigned)time(NULL));
	level = 1;
	enemyCreateTime = GetTickCount();
	enemyCreateCount = 0;
	enemyNowCount = 0;
	for (int i = 0; i < 4; ++i)
	{
		upgradeAD[i] = 0;
	}
}

void Game::Progress()
{
	srand(GetTickCount());

	DWORD dwKey = KeyManager::GetInst()->GetKey();

#pragma region Player
	
	player->Progress();

#pragma endregion

#pragma region Tower

	// Å¸¿ö »ý¼º
	if (dwKey & KEY_SPACE && player->GetGold() >= 10)
	{
		for (int i = 0; i < TowerCount; ++i)
		{
			if (!tower[i]->GetAct())
			{
				bool check = true;
				for (int j = 0; j < i; ++j)
				{
					if (CollisionManager::GetInst()->CollisionCheck(player, tower[j])) 
					{
						check = false;
						break;
					}
				}
				if (check)
				{
					tower[i]->SetAct(true);
					if (player->info.x >= 26)
						tower[i]->info.x = player->info.x - (player->info.x - 25);
					else
						tower[i]->info.x = player->info.x;

					if (player->info.y > 25)
						tower[i]->info.y = player->info.y - (player->info.y - 25);
					else
						tower[i]->info.y = player->info.y;

					player->SetGold(player->GetGold() - 10);
					break;
				}
			}
		}
	}

#pragma endregion

#pragma region Bullet
	// Å¸¿ö ºÒ·¿ »ý¼º
	for (int i = 0; i < TowerCount; ++i)
	{
		if (tower[i]->GetAct() && !bullets[i]->GetAct() && (tower[i]->GetAttackTime() + tower[i]->GetSpeed() < GetTickCount()))
		{
			tower[i]->SetAttackTime(GetTickCount());

			for (int j = 0; j < EnemyCount; ++j)
			{
				if (enemies[j]->GetAct() && sqrt(pow(tower[i]->info.x - enemies[j]->info.x, 2) +
					pow(tower[i]->info.y - enemies[j]->info.y, 2)) <= 15)
				{
					bullets[i]->SetAct(true);
					bullets[i]->SetTarget(j);
					bullets[i]->SetState(tower[i]->GetState());
					bullets[i]->info.x = tower[i]->info.x - bullets[i]->info.cx;
					bullets[i]->info.y = tower[i]->info.y + bullets[i]->info.cy;
					if (tower[i]->info.x < enemies[j]->info.x)
					{
						bullets[i]->info.x = tower[i]->info.x + tower[i]->info.cx;
					}
					break;
				}
			}
		}
	}

	// ºÒ·¿ °ª º¯°æ
	for (int i = 0; i < BulletCount; i++)
	{
		if (bullets[i]->GetAct() && enemies[bullets[i]->GetTarget()]->GetAct())
		{
			float fX = enemies[bullets[i]->GetTarget()]->info.x - bullets[i]->info.x;
			float fY = enemies[bullets[i]->GetTarget()]->info.y - bullets[i]->info.y;
			float fDistance = sqrt(pow(fX, 2) + pow(fY, 2));

			bullets[i]->SetDirectionX(fX / fDistance);
			bullets[i]->SetDirectionY(fY / fDistance);

			bullets[i]->Progress();
			if (tower[i]->GetState() == NOMAL && tower[i]->info.x < enemies[bullets[i]->GetTarget()]->info.x)
			{
				bullets[i]->shape[1] = "¤Ñ¤Ñ¢º";
			}
		}
		else if (bullets[i]->GetAct())	// Å¸°Ù ÀûÀÌ ¾øÀ» °æ¿ì ºÒ·¿ »èÁ¦
		{
			bullets[i]->SetAct(false);
		}

		// ºÒ·¿ <-> Àû Ãæµ¹
		if (bullets[i]->GetAct() && enemies[bullets[i]->GetTarget()]->GetAct() && CollisionManager::GetInst()->CollisionCheck(bullets[i], enemies[bullets[i]->GetTarget()]))
		{
			switch (tower[i]->GetState())
			{
			case ICE:
				switch (rand() % 10)
				{
				case 0: case 2: case 4: case 6: case 8:
					enemies[bullets[i]->GetTarget()]->SetState(ICE);
					enemies[bullets[i]->GetTarget()]->SetStateTime(GetTickCount());
				}
				break;

			case STURN:
				switch (rand() % 10)
				{
				case 0: case 2: case 4:
					enemies[bullets[i]->GetTarget()]->SetState(STURN);
					enemies[bullets[i]->GetTarget()]->SetStateTime(GetTickCount());
				}
				break;

			case SPLASH:
				for (int j = 0; j < enemyCreateCount; ++j)
				{
					if (j == bullets[i]->GetTarget()) continue;

					float distance = sqrt(pow(enemies[bullets[i]->GetTarget()]->info.x - enemies[j]->info.x, 2) +
						pow(enemies[bullets[i]->GetTarget()]->info.y - enemies[j]->info.y, 2));

					if (enemies[j]->GetAct() && distance <= 15)	// °Å¸® °í¹ÎÇØº¸±â.
					{
						int hp = enemies[j]->GetHP() - (tower[i]->GetAD() +  upgradeAD[tower[i]->GetState()]);
						if (hp <= 0)
						{
							player->SetGold(player->GetGold() + enemies[j]->GetGold());
							enemies[j]->SetAct(false);
							--enemyNowCount;
						}
						else
							enemies[j]->SetHP(hp);
					}
				}
				break;
			}

			int hp = enemies[bullets[i]->GetTarget()]->GetHP() - (tower[i]->GetAD() + upgradeAD[tower[i]->GetState()]);

			if (hp <= 0)
			{
				player->SetGold(player->GetGold() + enemies[bullets[i]->GetTarget()]->GetGold());
				enemies[bullets[i]->GetTarget()]->SetAct(false);
				bullets[i]->SetAct(false);
				--enemyNowCount;
			}
			else
			{
				enemies[bullets[i]->GetTarget()]->SetHP(hp);
				bullets[i]->SetAct(false);
			}
		}
	}
#pragma endregion
	
#pragma region Enemy

	if (enemyCreateTime + 1000 < GetTickCount())
	{
		enemyCreateTime = GetTickCount();

		if (enemyCreateCount != EnemyCount)
		{
			// µ·, hp ¼³Á¤ÇÏ±â
			enemies[enemyCreateCount]->SetHP(level + (rand() % level) * 2);
			enemies[enemyCreateCount]->SetGold(1 + (rand() % level) / 2);
			enemies[enemyCreateCount]->SetAct(true);
			enemies[enemyCreateCount]->SetState(NOMAL);
			enemies[enemyCreateCount]->info.color = Èò»ö;
			enemies[enemyCreateCount]->info.x = 3;
			enemies[enemyCreateCount]->info.y = 0;
			++enemyCreateCount;
			++enemyNowCount;
		}
	}

	for (int i = 0; i < enemyCreateCount; ++i)
	{
		if(enemies[i]->GetAct())
			enemies[i]->Progress();
	}

	// ¸ó½ºÅÍ ¸øÀâ¾ÒÀ» °æ¿ì
	for (int i = 0; i < enemyCreateCount; ++i)
	{
		if (enemies[i]->GetAct() && enemies[i]->info.y <= 0)
		{
			enemies[i]->SetAct(false);
			--enemyNowCount;
			player->SetHP(player->GetHP() - 1);
			if (player->GetHP() == 0)
				StateManager::GetInst()->SetState(END);		// ³ªÁß¿¡ END·Î ¹Ù²ãÁÖ±â
		}
	}

#pragma endregion
	// ´ÙÀ½ ¶ó¿îµå °¡±â
	if (enemyNowCount == 0 && enemyCreateCount == EnemyCount)
	{
		++level;
		enemyCreateCount = 0;
	}

	// ¾÷±×·¹ÀÌµå
	if (dwKey & KEY_UPGRADE && player->GetGold() >= 30)
	{
		player->SetGold(player->GetGold() - 30);
		switch (rand() % 4) {
		case NOMAL:
			upgradeAD[NOMAL] += rand() % 3;
			break;
		case ICE:
			upgradeAD[ICE] += rand() % 3;
			break;
		case STURN:
			upgradeAD[STURN] += rand() % 3;
			break;
		case SPLASH:
			upgradeAD[SPLASH] += rand() % 2;
			break;
		}
	}

	// ·£´ý µ· »Ì±â
	if (dwKey & KEY_RANDOM10 && player->GetGold() >= 10)
		player->SetGold(player->GetGold() + (rand() % 20 - 10));

	if (dwKey & KEY_RANDOM50 && player->GetGold() >= 50)
		player->SetGold(player->GetGold() + (rand() % 100 - 50));

	if (dwKey & KEY_RANDOM300 && player->GetGold() >= 300)
		player->SetGold(player->GetGold() + (rand() % 600 - 300));
}

void Game::Render()
{
	int yLine = 3;
	char Level[16];
	char Gold[16];
	char upgrade_Nomal[16];
	char upgrade_Ice[16];
	char upgrade_Sturn[16];
	char upgrade_Splash[16];
	itoa(level, Level, 10);
	itoa(player->GetGold(), Gold, 10);
	itoa(upgradeAD[0], upgrade_Nomal, 10);
	itoa(upgradeAD[1], upgrade_Ice, 10);
	itoa(upgradeAD[2], upgrade_Sturn, 10);
	itoa(upgradeAD[3], upgrade_Splash, 10);

	char xx[4];
	char yy[4];
	itoa(player->info.x, xx, 10);
	itoa(player->info.y, yy, 10);

	DoubleBuffer::GetInst()->WriteBuffer(20, 4, xx, Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(20, 5, yy, Èò»ö);

	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "HP : ", Èò»ö);
	for (int i = 0; i < player->GetHP(); ++i)
	{
		DoubleBuffer::GetInst()->WriteBuffer(94 + i * 2, yLine, "¢¾", ¹àÀº»¡°£»ö);
	}

	yLine = 5;

	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "·¹º§ : ", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(97, yLine++, Level, Èò»ö);

	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "°ñµå : ", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(97, yLine, Gold, Èò»ö);

	yLine = 9;
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine++, "¾÷±×·¹ÀÌµå", Èò»ö);

	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "NOMAL : ", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(98, yLine++, upgrade_Nomal, Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "ICE : ", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(96, yLine++, upgrade_Ice, Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "STURN : ", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(98, yLine++, upgrade_Sturn, Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "SPLASH : ", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(99, yLine++, upgrade_Splash, Èò»ö);

	yLine = 17;
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine++, "·£´ýµ· »Ì±â", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine++, "Q(10¿ø) : 0 ~ 20¿ø", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine++, "W(50¿ø) : 0 ~ 100¿ø", Èò»ö);
	DoubleBuffer::GetInst()->WriteBuffer(90, yLine, "E(300¿ø) : 0 ~ 600¿ø", Èò»ö);

	map->Render();

	player->Render();

	for (int i = 0; i < TowerCount; ++i)
	{
		if (tower[i]->GetAct())
		{
			tower[i]->Render();
		}
	}

	for (int i = 0; i < BulletCount; ++i)
	{
		if(bullets[i]->GetAct())
			bullets[i]->Render();
	}

	for (int i = 0; i < EnemyCount; ++i)
	{
		if (enemies[i]->GetAct())
			enemies[i]->Render();
	}
}

void Game::Release()
{

	player->Release();

	for (int i = 0; i < BulletCount; ++i)
	{
		bullets[i]->Release();
	}

	for (int i = 0; i < TowerCount; ++i)
	{
		tower[i]->Release();
	}

	for (int i = 0; i < EnemyCount; ++i)
	{
		enemies[i]->Release();
	}
}

Game::Game()
{
}


Game::~Game()
{
}
