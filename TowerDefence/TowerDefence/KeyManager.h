#pragma once
#include "Include.h"
class KeyManager
{
private:
	static KeyManager* pInst;
public:
	static KeyManager* GetInst()
	{
		if (pInst == nullptr)
		{
			pInst = new KeyManager;
		}

		return pInst;
	}
private:
	DWORD dwKey;
public:
	DWORD GetKey()
	{
		return dwKey;
	}
public:
	void CheckKey();
public:
	KeyManager();
	~KeyManager();
};

