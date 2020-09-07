#pragma once

#include <Windows.h>
#include <cstdio>
#include <vector>
#include <map>
#include <list>
#include <fstream>

extern int g_Bullet;

using namespace std;

typedef struct CropRect
{
	DWORD x;
	DWORD y;
	DWORD width;
	DWORD height;
}CRECT;

enum Obstacle
{
	GROUND = 0,
	BOTTOMFORK,
	TOPFORK,
	AWL,

};

enum MoveType
{
	WALK = 0,
	JUMP,
	DJUMP,
	SLIDE,
	FALL,
};

enum class MoveType2
{
	WALK = 0,
	JUMP,
	DJUMP,
	SLIDE,
	NOMAL,
};

enum Direction
{
	VERTICAL,
	LEFT,
	RIGHT,
};

enum BossType
{
	IDLE,
	ATTACK1,
	ATTACK2,
	CHANGE,
	RUSH,
	FIRE,
	DIE
};

#define BTN_STATE_NOMAL		0x0000
#define BTN_STATE_HOVER		0x0001
#define BTN_STATE_CLICKED	0x0002

#define TAG_START_BUTTON	"tag_start_btn"
#define	TAG_EXIT_BUTTON		"tag_exit_btn"

#define TILE_SIZE 64
#define ORI_TILE_SIZE 128

#define TILE_NUM_X	10
#define TILE_NUM_Y	10

#define GROUND_NUM	20

// GameDirector 게임 동작
// PrepareWnd	윈도우 클래스 정보
// WrappedWnd	메시지 처리
