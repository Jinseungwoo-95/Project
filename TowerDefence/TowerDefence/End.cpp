#include "End.h"
#include "KeyManager.h"
#include "StateManager.h"
#include "DoubleBuffer.h"


void End::Initialize()
{
	selectEnd = END_RESTART;
	shape[0] = "  /$$$$$$   /$$$$$$  /$$      /$$ /$$$$$$$$        /$$$$$$  /$$    /$$ /$$$$$$$$ /$$$$$$$";
	shape[1] = " /$$__  $$ /$$__  $$| $$$    /$$$| $$_____/       /$$__  $$| $$   | $$| $$_____/| $$__  $$";
	shape[2] = "| $$  |__/| $$    $$| $$$$  /$$$$| $$            | $$    $$| $$   | $$| $$      | $$   $$";
	shape[3] = "| $$ /$$$$| $$$$$$$$| $$ $$/$$ $$| $$$$$         | $$  | $$|  $$  /$$/| $$$$$   | $$$$$$$/";
	shape[4] = "| $$|_  $$| $$__  $$| $$  $$$| $$| $$__/         | $$  | $$    $$ $$/ | $$__/   | $$___ $$";
	shape[5] = "| $$    $$| $$  | $$| $$  $  | $$| $$            | $$  | $$     $$$/  | $$      | $$     $$";
	shape[6] = "|  $$$$$$/| $$  | $$| $$ /   | $$| $$$$$$$$      |  $$$$$$/      $/   | $$$$$$$$| $$     |$$";
	shape[7] = "|_______/ |__/  |__/|___/    |__/|________/      |_______/      _/    |________/|__/     |__/";
}

void End::Progress()
{
	DWORD dwKey = KeyManager::GetInst()->GetKey();

	if (dwKey & KEY_UP)
		selectEnd = END_RESTART;

	if (dwKey & KEY_DOWN)
		selectEnd = END_EXIT;

	if (dwKey & KEY_RETURN)
	{
		switch (selectEnd)
		{
		case END_RESTART:
			StateManager::GetInst()->SetState(GAME);
			break;

		case END_EXIT:
			StateManager::GetInst()->SetState(EXIT);
			break;
		}
	}
}

void End::Render()
{
	srand(GetTickCount());
	int color = rand() % 16;
	for (int i = 0; i < 8; ++i)
	{
		DoubleBuffer::GetInst()->WriteBuffer(13, 8 + i, shape[i], color);
	}

	switch (selectEnd)
	{
	case END_RESTART:
		
		DoubleBuffer::GetInst()->WriteBuffer(45, 23, "게임을 다시 하시겠습니까 ?", 흰색);

		DoubleBuffer::GetInst()->WriteBuffer(52, 25, "▶ ", 밝은노란색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 25, "YES", 밝은노란색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 27, "N O", 흰색);
		break;

	case END_EXIT:
		DoubleBuffer::GetInst()->WriteBuffer(45, 23, "게임을 다시 하시겠습니까 ?", 흰색);
		DoubleBuffer::GetInst()->WriteBuffer(52, 27, "▶ ", 밝은노란색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 25, "YES", 흰색);
		DoubleBuffer::GetInst()->WriteBuffer(55, 27, "N O", 밝은노란색);
		break;
	}
}

void End::Release()
{
}

End::End()
{
}


End::~End()
{
}
