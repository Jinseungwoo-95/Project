#include "Player.h"
#include "ObjFactory.h"
#include "DoubleBuffer.h"
#include "KeyManager.h"

void Player::Initialize()
{
	info.x = 17;
	info.y = 15;
	shape[0] = "¡¡¡Û";
	shape[1] = "¢ÐHH¢Ñ";
	shape[2] = "¡¡HH";
	shape[3] = " ¢×¢Ù";
	info.cx = 6;
	info.cy = 6;
	info.color = ¹àÀº»¡°£»ö;
	gold = 10;
	hp = 10;
}

void Player::Progress()
{
	DWORD dwKey = KeyManager::GetInst()->GetKey();

	if (dwKey & KEY_LEFT && info.x >9)
	{
		info.x--;
	}

	if (dwKey & KEY_RIGHT && info.x < 28)
	{
		info.x++;
	}

	if (dwKey & KEY_UP && info.y >0)
	{
		info.y--;
	}

	if (dwKey & KEY_DOWN && info.y < 27)
	{
		info.y++;
	}
}

void Player::Render()
{
	for (int i = 0; i < PlayerHeight; i++)
	{
		DoubleBuffer::GetInst()->WriteBuffer(info.x * 2, info.y + i, shape[i], info.color);
	}
}

void Player::Release()
{
}

int Player::GetHP()
{
	return hp;
}

void Player::SetHP(int _hp)
{
	hp = _hp;
}

int Player::GetGold()
{
	return gold;
}

void Player::SetGold(int _gold)
{
	gold = _gold;
}

Player::Player()
{
}


Player::~Player()
{
}
