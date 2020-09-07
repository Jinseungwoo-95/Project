#pragma once
#include "Include.h"

class DoubleBuffer
{
private:
	static DoubleBuffer* pInst;
public:
	static DoubleBuffer* GetInst()
	{
		if (pInst == nullptr)
		{
			pInst = new DoubleBuffer;
		}
		return pInst;
	}
private:
	static int screenIndex;
	static HANDLE hBuffer[2];
public:
	//버퍼 초기화
	void InitDoubleBuffer();
	//버퍼에다가 쓰는 용도
	void WriteBuffer(int x, int y, const char* shape, int color);
	//버퍼를 뒤집어 주는 아이
	void FlipBuffer();
	//버퍼를 깨끗하게 만들어주는 아이
	void ClearBuffer();
	//버퍼를 해제시켜 주는 아아
	void DestroyBuffer();

public:
	DoubleBuffer();
	~DoubleBuffer();
};
