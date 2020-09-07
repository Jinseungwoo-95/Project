#pragma once
#include "StateObj.h"
#include "Include.h"

class End : public StateObj
{
private:
	SELEND selectEnd;
	const char* shape[8];

public:
	virtual void Initialize();
	virtual void Progress();
	virtual void Render();
	virtual void Release();

public:
	End();
	~End();
};

