#pragma once
#include "StateObj.h"
class StateManager 
{
private:
	static StateManager* pInst;
public:
	static StateManager* GetInst()
	{
		if (pInst == nullptr)
		{
			pInst = new StateManager;
		}

		return pInst;
	}
private:
	StateObj* pState;
public:
	void SetState(STATE_ID state);
	void Progress();
	void Render();
	void Release();
public:
	StateManager();
	~StateManager();
};

