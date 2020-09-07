#include "Enemy.h"
#include "DoubleBuffer.h"

void Enemy::Initialize()
{
	act = false;
	info.x = 0;
	info.y = 0;
	shape[0] = "¡¡¡ã";
	shape[1] = "¢¸¡Û¢º";
	shape[2] = "¡¡¡å";
	info.cx = 5;
	info.cy = EnemyHeight;
	info.color = Èò»ö;
	state = NOMAL;
	stateTime = GetTickCount();
	hp = 0;
	gold = 0;
}

void Enemy::Progress()
{
	switch (state)
	{
	case ICE:
		info.color = ¹àÀºÆÄ¶õ»ö;
		if (stateTime + 500 < GetTickCount())
		{
			state = NOMAL;
			info.color = Èò»ö;
		}
		if (info.x == 3 && info.y < BufferHeight - (EnemyHeight + 3))
			info.y += 0.5;
		else if (info.x < BufferHeight - (EnemyHeight + 3))
			info.x += 0.5;
		else
			info.y -= 0.5;
		break;
	case STURN:
		info.color = ¹àÀº³ë¶õ»ö;
		if (stateTime + 500 < GetTickCount())
		{
			state = NOMAL;
			info.color = Èò»ö;
		}
		break;
	default:
		if (info.x == 3 && info.y < BufferHeight - (EnemyHeight + 3))
			info.y += 1;
		else if (info.x < BufferHeight - (EnemyHeight + 3))
			info.x += 1;
		else
			info.y -= 1;
		break;
	}
}

void Enemy::Render()
{
	for (int i = 0; i < EnemyHeight; i++)
		DoubleBuffer::GetInst()->WriteBuffer(info.x * 2, info.y + i, shape[i], info.color);
}

void Enemy::Release()
{
}

void Enemy::SetAct(bool _act)
{
	act = _act;
}

bool Enemy::GetAct()
{
	return act;
}

int Enemy::GetHP()
{
	return hp;
}

void Enemy::SetHP(int _hp)
{
	hp = _hp;
}

int Enemy::GetGold()
{
	return gold;
}

void Enemy::SetGold(int _gold)
{
	gold = _gold;
}

void Enemy::SetState(STATE _state)
{
	state = _state;
}

void Enemy::SetStateTime(int _stateTime)
{
	stateTime = _stateTime;
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
