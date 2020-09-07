#include "CollisionManager.h"

CollisionManager* CollisionManager::pInst = nullptr;

bool CollisionManager::CollisionCheck(Obj * obj1, Obj * obj2)
{
	if (obj1->info.x < obj2->info.x + obj2->info.cx &&
		obj2->info.x < obj1->info.x + obj1->info.cx &&
		obj1->info.y < obj2->info.y + obj2->info.cy &&
		obj2->info.y < obj1->info.y + obj1->info.cy )
	{
		return true;
	}

	return false;
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
