#include "Menu.h"
#include "KeyManager.h"
#include "StateManager.h"
#include "DoubleBuffer.h"

void Menu::Initialize()
{
	shape[0] = "　  / $$$$$$$   /$$$$$$   /$$   /$$  /$$$$$$$    $$$$$$$   /$$       /$$";
	shape[1] = "　 | $$__  $$  /$$__  $$ | $$$ | $$ | $$__  $$  /$$__  $$ | $$$     /$$$";
	shape[2] = "　 | $$  | $$ | $$  | $$ | $$$$| $$ | $$  $ $$ | $$  $ $$ | $$$$   /$$$$";
	shape[3] = "　 | $$$$$$/  | $$$$$$$$ | $$ $$ $$ | $$  | $$ | $$  | $$ | $$ $$ /$$ $$";
	shape[4] = "　 | $$___ $$ | $$__  $$ | $$  $$$$ | $$  | $$ | $$  | $$ | $$  $$$ | $$";
	shape[5] = " 　| $$   |$$ | $$  | $$ | $$*  $$$ | $$  | $$ | $$  | $$ | $$   $  | $$";
	shape[6] = "　 | $$   |$$ | $$  | $$ | $$ *  $$ | $$$$$$$/ |  $$$$$$/ | $$      | $$";
	shape[7] = "　 |__/   |_/ |__/  |__/ |__/  *__/ |_______/  |_______/  |__/      |__/";
	shape[8] = " /$$$$$$$   /$$$$$$$$$ / $$$$$$$$  /$$$$$$$$ /$$   /$$  /$$$$$$   /$$$$$$$$";
	shape[9] = "| $$__  $$ | $$_____/ | $$_____/  | $$_____/| $$$ | $$ |$$    $$ | $$_____/";
	shape[10] = "| $$  | $$ | $$       | $$        | $$      | $$$$| $$  |$$      | $$";
	shape[11] = "| $$  | $$ | $$$$$$   | $$$$$     | $$$$$   | $$ $$ $$   |$$$$$$ | $$$$$";
	shape[12] = "| $$  | $$ | $$__/    | $$__/     | $$__/   | $$  $$$$  __    $$ | $$__/";
	shape[13] = "| $$  | $$ | $$       | $$        | $$      | $$   $$$ /$$   $$  | $$";
	shape[14] = "| $$$$$$$/ | $$$$$$$$ | $$        | $$$$$$$$| $$    $$ |$$$$$$$/ | $$$$$$$$";
	shape[15] = "|_______/  |________/ |__/        |________/|__/   __/  ______/  |________/";
	selectMenu = GAME_START;
}

void Menu::Progress()
{
	DWORD dwKey = KeyManager::GetInst()->GetKey();

	if (dwKey & KEY_UP)
		selectMenu = GAME_START;
	
	if (dwKey & KEY_DOWN)
		selectMenu = GAME_EXIT;

	if (dwKey & KEY_RETURN)
	{
		switch (selectMenu)
		{
		case GAME_START:
			StateManager::GetInst()->SetState(GAME);
			break;

		case GAME_EXIT:
			StateManager::GetInst()->SetState(EXIT);
			break;
		}
	}
}

void Menu::Render()
{
	srand(GetTickCount());
	int color = rand() % 16;
	for (int i = 0; i < 15; ++i)
	{
		DoubleBuffer::GetInst()->WriteBuffer(23, 5 + i, shape[i], color);
	}

	switch (selectMenu)
	{
	case GAME_START:
		DoubleBuffer::GetInst()->WriteBuffer(52, 25, "▶ ", 밝은노란색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 25, "게임시작", 밝은노란색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 27, "종 료", 흰색);
		break;

	case GAME_EXIT:
		DoubleBuffer::GetInst()->WriteBuffer(52, 27, "▶ ", 밝은노란색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 25, "게임시작", 흰색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 27, "종 료", 밝은노란색);
		break;
	}
}

void Menu::Release()
{
}

Menu::Menu()
{
}


Menu::~Menu()
{
}
