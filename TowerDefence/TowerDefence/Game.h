#pragma once
#include "StateObj.h"
#include "ObjFactory.h"
#include "Map.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "Tower.h"

class Game : public StateObj
{
private:
	Player* player;
	Enemy* enemies[EnemyCount];
	Tower* tower[TowerCount];
	Bullet* bullets[BulletCount];
	Map* map;
private:
	int level;
	int enemyCreateTime;
	int enemyCreateCount;
	int enemyNowCount;
	int upgradeAD[4];
public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	Game();
	~Game();
};

