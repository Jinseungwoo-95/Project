#pragma once
#include "Obj.h"
#include "Player.h"

class Tower : public Obj
{
private:
	bool act;
	const char* shape[TowerHeight];
	int speed;
	int attackTime;
	int ad;
	STATE state;

public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

	bool GetAct();
	void SetAct(bool _act);

	int GetSpeed();
	int GetAD();

	int GetAttackTime();
	void SetAttackTime(int _attackTime);


	STATE GetState();
public:
	Tower();
	~Tower();
};

