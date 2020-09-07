#include "Tower.h"
#include "DoubleBuffer.h"

void Tower::Initialize()
{
	act = false;
	switch (rand() % 4) //rand() % 4
	{
	case 0:
		state = NOMAL;
		speed = 500;
		ad = 2;
		shape[0] = "¡¡¡¡¡á";
		shape[1] = "¡¡¡á¡à¡á";
		shape[2] = "¡á¡à¡à¡à¡á";
		shape[3] = "¡¡¡á¡á¡á";
		shape[4] = "¡¡¡á¡á¡á";
		shape[5] = "¡¡¡á¡á¡á";
		info.color = Èò»ö;
		break;
	case 1:
		state = ICE;
		speed = 750;
		ad = 1;
		shape[0] = " #  #  #";
		shape[1] = "  # # #";
		shape[2] = " #######";
		shape[3] = "  # # #";
		shape[4] = " #  #  #";
		shape[5] = "";
		info.color = ÆÄ¶õ»ö;
		break;
	case 2:
		state = STURN;
		speed = 750;
		ad = 1;
		shape[0] = "¡¡£À£À£À";
		shape[1] = " £À £À  £À";		// 
		shape[2] = "£À £À £À £À ";
		shape[3] = "£À £À    £À ";
		shape[4] = " £À¡¡£À£À ";
		shape[5] = "¡¡£À£À£À£À ";
		info.color = ³ë¶õ»ö;
		break;
	case 3:
		state = SPLASH;
		speed = 1000;
		ad = 1;
		shape[0] = "¡á¡á¡á¡á¡á";
		shape[1] = "¡¡¡¡¡á¡á¡á";
		shape[2] = "¡ø¡à¡à¡á¡á";
		shape[3] = "¡¡¡¡¡á¡á¡á";
		shape[4] = "¡á¡á¡á¡á¡á";
		shape[5] = "";
		info.color = ¹àÀº»¡°£»ö;
		break;
	}
	attackTime = GetTickCount();
	info.x = 0;
	info.y = 0;
	info.cx = 6;
	info.cy = TowerHeight;
}

void Tower::Progress()
{
}

void Tower::Render()
{
	for (int i = 0; i < TowerHeight; i++)
	{
		DoubleBuffer::GetInst()->WriteBuffer(info.x * 2, info.y + i, shape[i], info.color);
	}
}

void Tower::Release()
{
}

bool Tower::GetAct()
{
	return act;
}

void Tower::SetAct(bool _act)
{
	act = _act;
}

int Tower::GetSpeed()
{
	return speed;
}

int Tower::GetAD()
{
	return ad;
}

int Tower::GetAttackTime()
{
	return attackTime;
}

void Tower::SetAttackTime(int _attackTime)
{
	attackTime = _attackTime;
}

STATE Tower::GetState()
{
	return state;
}

Tower::Tower()
{
}


Tower::~Tower()
{
}
