#include "DoubleBuffer.h"

DoubleBuffer* DoubleBuffer::pInst = nullptr;
int DoubleBuffer::screenIndex = 0;
HANDLE DoubleBuffer::hBuffer[2];


void DoubleBuffer::InitDoubleBuffer()
{
	COORD size = { BufferWidth, BufferHeight };
	CONSOLE_CURSOR_INFO info;
	SMALL_RECT rect = { 0, 0, BufferWidth - 1, BufferHeight - 1 };

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	info.dwSize = 1;
	info.bVisible = false;

	SetConsoleCursorInfo(hBuffer[0], &info);
	SetConsoleCursorInfo(hBuffer[1], &info);
}

void DoubleBuffer::WriteBuffer(int x, int y, const char* shape, int color)
{
	DWORD dw;
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hBuffer[screenIndex], pos);
	SetConsoleTextAttribute(hBuffer[screenIndex], color);
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);
}

void DoubleBuffer::FlipBuffer()
{
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);
	screenIndex = !screenIndex;
}

void DoubleBuffer::ClearBuffer()
{
	COORD pos = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}

void DoubleBuffer::DestroyBuffer()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}

DoubleBuffer::DoubleBuffer()
{
}


DoubleBuffer::~DoubleBuffer()
{
}
