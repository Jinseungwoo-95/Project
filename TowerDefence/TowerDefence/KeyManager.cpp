#include "KeyManager.h"

KeyManager* KeyManager::pInst = nullptr;

void KeyManager::CheckKey()
{
	dwKey = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		dwKey |= KEY_UP;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		dwKey |= KEY_DOWN;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		dwKey |= KEY_LEFT;
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		dwKey |= KEY_RIGHT;
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		dwKey |= KEY_SPACE;
	
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		dwKey |= KEY_RETURN;

	if (GetAsyncKeyState('U') & 0x8000)
		dwKey |= KEY_UPGRADE;

	if (GetAsyncKeyState('Q') & 0x8000)
		dwKey |= KEY_RANDOM10;
	if (GetAsyncKeyState('W') & 0x8000)
		dwKey |= KEY_RANDOM50;
	if (GetAsyncKeyState('E') & 0x8000)
		dwKey |= KEY_RANDOM300;
}

KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}
