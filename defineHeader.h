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
	IMAGE_TYPE_IMG,
	IMAGE_TYPE_FRAMEIMG
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
	STATE_TYPE_IDLE,
	STATE_TYPE_TRACE,
	STATE_TYPE_ATTACK,
	STATE_TYPE_DEAD
};

enum class CHARACTER_TYPE
{
	PLAYER,
	GOOMBA,
	SKYTROOPA,
	SPIKEY
};

