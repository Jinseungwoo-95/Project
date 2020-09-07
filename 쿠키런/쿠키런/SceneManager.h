#pragma once
#include "GameDefine.h"

class Scene;
using namespace std;

class SceneManager
{
private:
	map<string, Scene*> m_SceneContainer;
	Scene* m_ReservedScene = nullptr;
	Scene* m_CurrentScene = nullptr;

	DWORD m_MousePositionX = 0;
	DWORD m_MousePositionY = 0;

public:
	void RegisterScene(const string& sceneName, Scene* scene);
	void reserveChangeScene(const string& sceneName);

public:
	void Update(float dt);
	void Render(HDC hdc, float dt);

public:
	DWORD GetMousePositionX();
	DWORD GetMousePositionY();

	void SetMousePosition(DWORD x, DWORD y);

public:
	SceneManager();
	~SceneManager();
};
