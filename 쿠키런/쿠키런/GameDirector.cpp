#include "GameDirector.h"

GameDirector::GameDirector()
{
	ApplicationHandle = this;
	m_SceneManager = new SceneManager;
	srand(GetTickCount());
}

GameDirector::~GameDirector()
{
	delete m_SceneManager;
}

GameDirector * GameDirector::GetGameDirector()
{
	static GameDirector dir;
	return &dir;
}

LRESULT GameDirector::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return ApplicationHandle->MessageHandler(hwnd, message, wParam, lParam);
	}
}

LRESULT GameDirector::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		m_SceneManager->SetMousePosition(LOWORD(lParam), HIWORD(lParam));	// LOWORD(lParam) X, HIWORD(lParam) Y
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void GameDirector::ProcessingLoop()
{
	static DWORD prevFrameTime = 10;	// 이전의 프레임타임 체크를하여 1프레임이 얼마나 시간 걸리는지 구하기위한것.
	if (m_FrameInterval + prevFrameTime < GetTickCount())
	{
		prevFrameTime = GetTickCount();

		HDC hdc = GetDC(m_hWnd);	// 계속 hdc를 생성해주는건가...??

		Update(((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);
		Render(hdc, ((float)GetTickCount() - (float)prevFrameTime) / 1000.0f);

		ReleaseDC(m_hWnd, hdc);
	}
}

void GameDirector::Update(float dt)
{
	m_SceneManager->Update(dt);
}

void GameDirector::Render(HDC hdc, float dt)
{
	HDC hMemDC;
	RECT windowRect;
	HBITMAP bitmap;

	GetClientRect(this->GetWndHandl(), &windowRect);

	hMemDC = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);

	SelectObject(hMemDC, bitmap);
	FillRect(hMemDC, &windowRect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	m_SceneManager->Render(hMemDC, dt);

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, hMemDC, 0, 0, SRCCOPY);
	DeleteObject(bitmap);
	DeleteDC(hMemDC);
}

void GameDirector::SetFrameInterval(DWORD interval)
{
	m_FrameInterval = interval;
}

DWORD GameDirector::GetFrameInterval()
{
	return m_FrameInterval;
}

SceneManager * GameDirector::GetSceneManager()
{
	return m_SceneManager;
}
