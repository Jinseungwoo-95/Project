#pragma once
#include "Object.h"

class Map2 : public Object
{
private:


public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();

	Map2();
	~Map2();
};

