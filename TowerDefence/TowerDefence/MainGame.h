#pragma once
#include "StateManager.h"
class MainGame
{
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();

public:
	MainGame();
	~MainGame();
};

