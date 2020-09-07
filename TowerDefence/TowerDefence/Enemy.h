#pragma once
#include "Obj.h"
class Enemy : public Obj
{
private:
	bool act;
	const char* shape[EnemyHeight];
	STATE state;
	int stateTime;
	int hp;
	int gold;

public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

	void SetAct(bool _act);
	bool GetAct();

	int GetHP();
	void SetHP(int _hp);

	int GetGold();
	void SetGold(int _gold);

	void SetState(STATE _state);
	void SetStateTime(int _stateTime);
public:
	Enemy();
	~Enemy();
};

