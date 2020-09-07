#pragma once

enum STATE_ID
{
	LOGO,
	MENU,
	GAME,
	END,
	EXIT,
};

enum COLOR
{
	검정색,
	파란색,
	초록색,
	옥색,
	빨간색,
	자주색,
	노란색,
	흰색,
	회색,
	밝은파란색,
	밝은초록색,
	밝은옥색,
	밝은빨간색,
	밝은자주색,
	밝은노란색,

};

enum  OBJ_ID
{
	PLAYER,
	TOWER,
	BULLET,
	ENEMY,
};

enum STATE
{
	NOMAL,
	ICE,
	STURN,
	SPLASH
};

enum SELMENU
{
	GAME_START,
	GAME_EXIT,
};

enum SELEND
{
	END_RESTART,
	END_EXIT,
};