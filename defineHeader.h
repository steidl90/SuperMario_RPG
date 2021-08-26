#pragma once
#define MAPSIZEX 1618
#define MAPSIZEY 1434

// 플레이어 속도를 위한 전역상수
const float runSpeed = 6.0f;
const float speed = 3.0f;
const int runAniFrame = 14;
const int aniFrame = 8;

enum class IMAGE_TYPE
{
	IMG,
	FRAMEIMG
};

enum class MOVE_TYPE
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	LEFTUP,
	LEFTDOWN,
	RIGHTUP,
	RIGHTDOWN,
	IDEL
};

enum class STATE_TYPE
{
	IDLE,
	MOVE,
	ATTACK,
	DEAD
};

enum class CHARACTER_TYPE
{
	PLAYER,
	GOOMBA,
	SKYTROOPA,
	SPIKEY
};

