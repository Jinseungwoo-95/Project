#pragma once
#include "Obj.h"
class CollisionManager
{
private:
	static CollisionManager* pInst;
public:
	static CollisionManager* GetInst()
	{
		if (pInst == nullptr)
		{
			pInst = new CollisionManager;
		}

		return pInst;
	}
public:
	bool CollisionCheck(Obj* obj1, Obj* obj2);
public:
	CollisionManager();
	~CollisionManager();
};

