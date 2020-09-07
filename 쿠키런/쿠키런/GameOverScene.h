#pragma once
#include "Scene.h"
#include "BackGround.h"
#include "Button.h"

class GameOverScene : public Scene
{
public:
	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(HDC hdc, float dt);
	virtual void Destroy();
private:
	BackGround		mBackGround;
	Button			m_StartButton;
	Button			m_ExitButton;

};

