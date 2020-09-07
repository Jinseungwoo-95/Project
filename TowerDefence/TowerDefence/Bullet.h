#pragma once
#include "Obj.h"
class Bullet : public Obj
{
private:
	bool act;
	int target;
	STATE state;
	float DirectionX;
	float DirectionY;
public:
	const char* shape[BulletHeight];
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

	void SetAct(bool _act);
	bool GetAct();

	void SetTarget(int _target);
	int GetTarget();

	void SetDirectionX(float _x);
	void SetDirectionY(float _y);

	void SetState(STATE _state);
public:
	Bullet();
	~Bullet();
};

