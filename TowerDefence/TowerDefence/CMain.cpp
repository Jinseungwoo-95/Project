#include "MainGame.h"

void main()
{
	MainGame game;
	game.Initialize();

	DWORD dwTime = GetTickCount();

	while (true)
	{
		if (dwTime + 50 < GetTickCount())
		{
			dwTime = GetTickCount();
			game.Progress();
			game.Render();
		}
	}

	game.Release();
}