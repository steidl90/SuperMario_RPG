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
	TRACE,
	BATTLE,
	DEAD
};

enum class CHARACTER_TYPE
{
	PLAYER_WORLD,
	PLAYER_BATTLE,

	MONSTER_WORLD,
	SKYTROOPA_WORLD,
	SPIKEY_WORLD,

	GOOMBA_BATTLE,
	SKYTROOPA_BATTLE,
	SPIKEY_BATTLE
};

enum class MONSTER_MOVE_TYPE
{
	RIGHTDOWN,
	LEFTDOWN,
	LEFTUP,
	RIGHTUP
};


//============================ zorder 용 ============================

//Z레이어설정
#define ZMAP		0
#define ZCOLMAP		1
#define ZUNIT		2
#define ZEFFECT		3
#define ZABOVEMAP	4
#define ZDEBUG		5

//최대레이어
#define ZMAXLAYER	5

//색상정의
#define MINT		RGB(88, 245, 206)

enum class ZORDERKIND
{
	IMG_NOMAL, IMG_NOMAL_SOUR, IMG_FRAME, IMG_ALPHA, IMG_ALPHA_SOUR, IMG_ALPHA_FRAME,
	IMG_ROTATE, IMG_STRETCH, IMG_STRETCH_FRAME, IMG_ANI
};

struct tagZorder
{
	ZORDERKIND kind;
	image* img;
	float destX, destY;
	float z;
	float bottom;
	int frameX, frameY;
	int sourX, sourY;
	int sourWidth, sourHeight;
	BYTE alpha;
	animation* ani;
	RECT rc;

	tagZorder(ZORDERKIND _kind, image* _img, int _z, int _x, int _y)
	{
		kind = _kind;
		img = _img;
		z = _z;
		destX = _x;
		destY = _y;
		frameX = frameY = sourX = sourY = sourWidth = sourHeight = alpha = alpha = bottom = NULL;
		ani = nullptr;
	}
};

//============================ zorder end ============================