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
	//���� �ʱ�ȭ
	void InitDoubleBuffer();
	//���ۿ��ٰ� ���� �뵵
	void WriteBuffer(int x, int y, const char* shape, int color);
	//���۸� ������ �ִ� ����
	void FlipBuffer();
	//���۸� �����ϰ� ������ִ� ����
	void ClearBuffer();
	//���۸� �������� �ִ� �ƾ�
	void DestroyBuffer();

public:
	DoubleBuffer();
	~DoubleBuffer();
};
