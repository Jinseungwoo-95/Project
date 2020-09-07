#pragma once
#include "Bitmap.h"

class Object
{

protected :
	Bitmap	mBitmap;
	int	mPosiX;
	int	mPosiY;

public:
	void SetX(int value) { mPosiX = value; }
	void SetY(int value) { mPosiY = value; }

	Bitmap* GetBitmap() { return &mBitmap; }
	int	GetX() { return mPosiX; }
	int	GetY() { return mPosiY; }

	virtual void Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render(HDC hdc, float dt) = 0;
	virtual void Destroy() = 0;
};