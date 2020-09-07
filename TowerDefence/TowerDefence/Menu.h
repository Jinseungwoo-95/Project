#pragma once
#include "StateObj.h"
#include "Include.h"

class Menu : public StateObj
{
private:
	SELMENU selectMenu;
	const char* shape[16];
public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();
public:
	Menu();
	~Menu();
};

