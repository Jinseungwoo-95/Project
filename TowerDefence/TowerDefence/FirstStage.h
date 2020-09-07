#pragma once
#include "Map.h"
class FirstStage : public Map
{
public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	FirstStage();
	~FirstStage();
};

