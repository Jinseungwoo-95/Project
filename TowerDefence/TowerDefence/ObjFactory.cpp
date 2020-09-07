#include "ObjFactory.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Tower.h"

ObjFactory* ObjFactory::pInst = nullptr;

Obj * ObjFactory::CreateObj(OBJ_ID id)
{
	Obj* obj = nullptr;

	switch (id)
	{
	case PLAYER:
		obj = new Player;
		break;
	case ENEMY:
		obj = new Enemy;
		break;
	case BULLET:
		obj = new Bullet;
		break;
	case TOWER:
		obj = new Tower;
		break;
	}

	obj->Initialize();

	return obj;
}

ObjFactory::ObjFactory()
{
}

ObjFactory::~ObjFactory()
{
}
