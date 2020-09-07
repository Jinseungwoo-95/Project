#pragma once
#include "Obj.h"
class ObjFactory
{
private:
	static ObjFactory* pInst;
public:
	static ObjFactory* GetInst()
	{
		if (pInst == nullptr)
		{
			pInst = new ObjFactory;
		}

		return pInst;
	}
public:
	Obj* CreateObj(OBJ_ID id);
public:
	ObjFactory();
	~ObjFactory();
};

