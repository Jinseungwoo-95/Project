#include "MainGame.h"
#include "DoubleBuffer.h"
#include "KeyManager.h"

void MainGame::Initialize()
{
	DoubleBuffer::GetInst()->InitDoubleBuffer();
	StateManager::GetInst()->SetState(MENU);

}

void MainGame::Progress()
{
	KeyManager::GetInst()->CheckKey();

	DoubleBuffer::GetInst()->FlipBuffer();
	DoubleBuffer::GetInst()->ClearBuffer();

	StateManager::GetInst()->Progress();

}

void MainGame::Render()
{

	StateManager::GetInst()->Render();
}

void MainGame::Release()
{	
	DoubleBuffer::GetInst()->DestroyBuffer();
	
	StateManager::GetInst()->Release();
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
