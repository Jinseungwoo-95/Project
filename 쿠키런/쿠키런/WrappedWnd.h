#pragma once
#include "GameDefine.h"
#include "PrepareWnd.h"

class WrappedWnd
{
public:
	// 밑에 4개 함수 호출
	int Loop(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);

private:
	void registerWndClass(const PrepareWnd& value);
	void createWindow(const PrepareWnd& value);
	void showWindw(const PrepareWnd& value);
	int MessageLoop();	// 처리할 메시지가 없을 때 ProcessingLoop() 호출

public:
	virtual void ProcessingLoop() = 0;

protected:
	HWND m_hWnd = nullptr;
	HINSTANCE m_hInstance = nullptr;

public:
	HWND GetWndHandl();
	HINSTANCE GetInstanceHandle();

public:
	WrappedWnd();
	~WrappedWnd();
};

