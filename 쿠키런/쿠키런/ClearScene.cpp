#include "ClearScene.h"

void ClearScene::Init()
{
	RECT rc = { 0,0,1280,670 };
	mBackGround.Init(const_cast<char*>("Clear.bmp"), rc);

	// ¹öÆ°
	RECT rc4 = { 800,240,1050,312 };
	m_StartButton.Init(const_cast<char*>("start_button.bmp"), rc4);
	m_StartButton.SetTag(const_cast<char*>(TAG_START_BUTTON));
	m_StartButton.SetTransparentColor(RGB(255, 0, 255));

	m_StartButton.GetButtonCropRect()[BTN_STATE_NOMAL] = { 0,0,200,72 };
	m_StartButton.GetButtonCropRect()[BTN_STATE_HOVER] = { 0,72,200,72 };
	m_StartButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142 ,200,72 };

	RECT rc5 = { 800,332,1050,404 };
	m_ExitButton.Init(const_cast<char*>("exit_button.bmp"), rc5);
	m_ExitButton.SetTag(const_cast<char*>(TAG_EXIT_BUTTON));
	m_ExitButton.SetTransparentColor(RGB(255, 0, 255));

	m_ExitButton.GetButtonCropRect()[BTN_STATE_NOMAL] = { 0,0,200,72 };
	m_ExitButton.GetButtonCropRect()[BTN_STATE_HOVER] = { 0,72,200,72 };
	m_ExitButton.GetButtonCropRect()[BTN_STATE_CLICKED] = { 0,142 ,200,72 };
}

void ClearScene::Update(float dt)
{
	mBackGround.Update(dt);
	m_StartButton.Update(dt);
	m_ExitButton.Update(dt);
}

void ClearScene::Render(HDC hdc, float dt)
{
	mBackGround.Render(hdc, dt);
	m_StartButton.Render(hdc, dt);
	m_ExitButton.Render(hdc, dt);
}

void ClearScene::Destroy()
{
	mBackGround.Destroy();
	m_StartButton.Destroy();
	m_ExitButton.Destroy();
}
