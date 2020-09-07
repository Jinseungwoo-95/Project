#pragma once
#include "Obj.h"
class Player : public Obj
{
private:
	const char* shape[PlayerHeight];
	int hp;
	int gold;

public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

	int GetHP();
	void SetHP(int _hp);
	int GetGold();
	void SetGold(int _gold);
public:
	Player();
	~Player();
};

