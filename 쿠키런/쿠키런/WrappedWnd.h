#pragma once
#include "GameDefine.h"
#include "PrepareWnd.h"

class WrappedWnd
{
public:
	// �ؿ� 4�� �Լ� ȣ��
	int Loop(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);

private:
	void registerWndClass(const PrepareWnd& value);
	void createWindow(const PrepareWnd& value);
	void showWindw(const PrepareWnd& value);
	int MessageLoop();	// ó���� �޽����� ���� �� ProcessingLoop() ȣ��

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

