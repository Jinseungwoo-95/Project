#include "GameDefine.h"
#include "GameDirector.h"
#include "SceneDefine.h"

int	g_Bullet = 500;

GameDirector* director = nullptr;

void InitScene();
void LoadScene(int index);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpCmdLine, int nCmdShow)
{
	InitScene();
	LoadScene(0);
	director->Loop(hInstance, lpCmdLine, nCmdShow);

}


void InitScene()
{
	director = GameDirector::GetGameDirector();
	director->GetSceneManager()->RegisterScene("MenuScene", new MenuScene);
	director->GetSceneManager()->RegisterScene("ClearScene", new ClearScene);
	director->GetSceneManager()->RegisterScene("GameOverScene", new GameOverScene);
	director->GetSceneManager()->RegisterScene("GameScene", new GameScene);
	director->GetSceneManager()->RegisterScene("GameScene2", new GameScene2);
}

void LoadScene(int index)
{
	switch (index)
	{
	case 0:
		director->GetSceneManager()->reserveChangeScene("MenuScene");
		break;
	case 1:
		director->GetSceneManager()->reserveChangeScene("GameScene");
		break;
	case 2:
		director->GetSceneManager()->reserveChangeScene("GameScene2");
		break;
	case 3:
		director->GetSceneManager()->reserveChangeScene("ClearScene");
		break;
	case 4:
		director->GetSceneManager()->reserveChangeScene("GameOverScene");
		break;
	}
}