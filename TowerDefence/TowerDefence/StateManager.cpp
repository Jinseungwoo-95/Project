#include "StateManager.h"
#include "Logo.h"
#include "Menu.h"
#include "Game.h"
#include "End.h"

StateManager* StateManager::pInst = nullptr;

void StateManager::SetState(STATE_ID state)
{
	if (pState != nullptr)
	{
		delete pState;
		pState = nullptr;
	}

	switch (state)
	{
	case MENU:
		pState = new Menu;
		break;
	case GAME:
		pState = new Game;
		break;
	case END:
		pState = new End;
		break;
	case EXIT:
		exit(true);
		break;
	default:
		break;
	}

	pState->Initialize();
}

void StateManager::Progress()
{
	pState->Progress();
}

void StateManager::Render()
{
	pState->Render();
}

void StateManager::Release()
{
	pState->Release();
}

StateManager::StateManager()
{
	pState = nullptr;
}


StateManager::~StateManager()
{
}
