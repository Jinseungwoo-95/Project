#include "Bullet.h"
#include "DoubleBuffer.h"

void Bullet::Initialize()
{
	act = false;
	info.x = 0;
	info.y = 0;
	shape[0] = " ###";
	shape[1] = "####";
	shape[2] = " ###";
	info.cx = 3;
	info.cy = BulletHeight;
	info.color = ���������;
	target = 0;
	DirectionX = 0;
	DirectionY = 0;
}

void Bullet::Progress()
{
	switch (state)
	{
	case ICE:
		shape[0] = " ##";
		shape[1] = "###";
		shape[2] = " ##";
		info.color = �����Ķ���;
		break;

	case STURN:
		shape[0] = " @@@";
		shape[1] = "@   @";
		shape[2] = " @@@";
		info.color = ���������;
		break;

	case NOMAL:
		shape[0] = "";
		shape[1] = "���Ѥ�";
		shape[2] = "";
		info.color = ���;
		break;

	case SPLASH:
		shape[0] = " �ܡ�";
		shape[1] = "�ܡܡ�";
		shape[2] = " �ܡ�";
		info.color = ����������;
		break;
	}

	info.x += 2 * DirectionX;
	info.y += 2 * DirectionY;
}

void Bullet::Render()
{
	if (act)
	{
		for (int i = 0; i < BulletHeight; i++)
		{
			DoubleBuffer::GetInst()->WriteBuffer(info.x * 2, info.y + i, shape[i], info.color);
		}
	}
}

void Bullet::Release()
{
}

void Bullet::SetAct(bool _act)
{
	act = _act;
}

bool Bullet::GetAct()
{
	return act;
}

void Bullet::SetTarget(int _target)
{
	target = _target;
}

int Bullet::GetTarget()
{
	return target;
}

void Bullet::SetDirectionX(float _x)
{
	DirectionX = _x;
}

void Bullet::SetDirectionY(float _y)
{
	DirectionY = _y;
}

void Bullet::SetState(STATE _state)
{
	state = _state;
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
