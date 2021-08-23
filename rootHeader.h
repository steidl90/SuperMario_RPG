#pragma once

// 카메라 크기
// 맵 사이즈
#define CAMERAWIDTH  WINSIZEX
#define CAMERAHEIGHT WINSIZEY
#define MAPTOOLPOINT (WINSIZEX - 30)

#define MAPSIZE TILEX * TILESIZE
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
/*

	맵 / 맵툴 관련

*/
//////////////////////////////////////////////
class frameObject;
class Citem;
// 툴용
// 샘플 타일 갯수
#define SAMPLETILEX 18
#define SAMPLETILEY 14

// 툴에서 사용할 기능,  현재 선택중인 CRTL에 따라 맵 타일 속성정의 등등
#define TILESIZE  36		//샘플 타일 이미지 사이즈
#define TILEX	  50		//맵 타일 x축 개수 
#define TILEY     50		//맵 타일 y축 개수

#define TILESIZEX TILEX * TILESIZE	// 맵 타일 전체 x축 사이즈(길이)
#define TILESIZEY TILEY * TILESIZE

enum class CTRL
{
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_ERASER,
	CTRL_FILL,
	CTRL_FRAME,
	CTRL_ERASERFRAME,
	CTRL_COLLISIONTILE,
	CTRL_ERASERCOLLISION
};

//지형 속성 종류
enum class TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//오브젝트 속성 종류
//(ex : 지형 위쪽에  배치, 움직이거나 부서지거나하는 변화를 줄수있는 물체)
enum class OBJECT
{
	OBJ_BLOCK1,
	OBJ_COLLISION,
	OBJ_NONE
};

enum class COLLISIONOBJECT
{
	COLLISIONOBJ,
	COLLISIONOBJ_NONE
};

enum class KINDFRAMEOBJECT
{
	GRASS_BIG,
	GRASS_SAMLL1,
	GRASS_SMALL2,
	NONE
};

enum class OBJECTIMAGE
{
	OBJECTIMAGE_TILE,
	OBJECTIMAGE_OBJECT1,
	OBJECTIMAGE_OBJECT2,
	OBJECTIMAGE_OBJECT3,
	OBJECTIMAGE_OBJECT4,
	OBJECTIMAGE_OBJECT5
};

enum class ATTRIBUTE
{
	COLLISION_OFF,
	COLLISION_ON
};

//오른쪽 타일 종류 변경 용도
enum class KINDSUBTILE
{
	KINDSUBTILE_DEFAULT,
	KINDSUBTILE_TREEONE,
	KINDSUBTILE_TREETWO,
	KINDSUBTILE_TREETHREE,
	KINDSUBTILE_HOUSEONE,
	KINDSUBTILE_HOUSETWO,
	KINDSUBTILE_HOUSETHREE,
	KINDSUBTILE_OBJECTONE,
	KINDSUBTILE_OBJECTTWO,
};

struct tagTileImage
{
	OBJECTIMAGE terrainImage;
	OBJECTIMAGE objImage;
};

//타일 구조체 (맵에 그릴 타일)
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	COLLISIONOBJECT collisionObj;
	RECT  rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
};

//샘플 (툴용) 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//현재 타일 구조체
struct tagCurrentTile
{
	int frame_x;
	int frame_y;

	OBJECTIMAGE terrainImage;
	OBJECTIMAGE objImage;
};

// 드래그 할시 시작 타일 인덱스 x,y 정보 끝 타일 인덱스 x, y 정보
struct tagDragTileIndex
{
	int index_StartX;
	int index_StartY;
	int index_EndX;
	int index_EndY;

	// 메인 맵에서 이용
	int frame_StartX;
	int frame_StartY;
	int frame_EndX;
	int frame_EndY;

	OBJECTIMAGE terrainImage;
	OBJECTIMAGE objImage;
};

struct tagFrameObjectInfo
{
	int check;
	KINDFRAMEOBJECT frame_kind;
};

struct tagFrameObject
{
	frameObject* frameObject;
	int index;
};

////////////////////////////////////
/*

	인벤토리, 아이템 관련

*/
////////////////////////////////////
enum class ITEMTYPE
{
	ITEMTYPE_WEAPON,
	ITEMTYPE_ARMOR,
	ITEMTYPE_SHOES,
	ITEMTYPE_GLOVES,
	ITEMTYPE_PENDANT,
	ITEMTYPE_POTION
};

struct EquipItem
{
	Citem* m_item;
	int m_itemIndex;
	POINT m_renderPoint;
	bool isEquip;
};

struct SelectItem
{
	Citem* m_item;
	int m_itemIndex;
	POINT m_renderPoint;
	bool isSelect;
};

////////////////////////////////////
/*

	몬스터 드랍 아이템

*/
////////////////////////////////////

struct DropItem
{
	Citem* item;
	float x;
	float y;
	RECT itemRect;
};

struct Potion
{
	image* image;
	int Count;
	int recoveryHp;
	int recoveryMp;
};