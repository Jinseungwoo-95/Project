#pragma once
#include "Include.h"
class Map
{
public:
	int map[MapHeight][MapWidth] = {0,};
public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	int GetMapInfo(int x, int y)
	{
		return map[y][x];
	}
public:
	Map();
	~Map();
};