#pragma once
#include "Include.h"
class Obj
{
public:
	INFO info;
public:
	virtual void Initialize()PURE;
	virtual void Progress()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
public:
	Obj();
	~Obj();
};

