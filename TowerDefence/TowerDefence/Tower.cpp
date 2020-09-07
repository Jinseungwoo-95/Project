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
		shape[0] = "������";
		shape[1] = "������";
		shape[2] = "������";
		shape[3] = "������";
		shape[4] = "������";
		shape[5] = "������";
		info.color = ���;
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
		info.color = �Ķ���;
		break;
	case 2:
		state = STURN;
		speed = 750;
		ad = 1;
		shape[0] = "��������";
		shape[1] = " �� ��  ��";		// 
		shape[2] = "�� �� �� �� ";
		shape[3] = "�� ��    �� ";
		shape[4] = " �������� ";
		shape[5] = "���������� ";
		info.color = �����;
		break;
	case 3:
		state = SPLASH;
		speed = 1000;
		ad = 1;
		shape[0] = "������";
		shape[1] = "��������";
		shape[2] = "�������";
		shape[3] = "��������";
		shape[4] = "������";
		shape[5] = "";
		info.color = ����������;
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
