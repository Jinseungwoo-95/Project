#include "MainGame.h"

int main()
{
	MainGame game;
	game.Initialize();

	DWORD dwTime = GetTickCount();

	while (true)
	{
		if (dwTime + 70 < GetTickCount())
		{
			dwTime = GetTickCount();
			game.Progress();
			game.Render();
		}
	}

	game.Release();

	return 0;
}