#pragma once

// ī�޶� ũ��
// �� ������
#define CAMERAWIDTH  WINSIZEX
#define CAMERAHEIGHT WINSIZEY
#define MAPTOOLPOINT (WINSIZEX - 30)

#define MAPSIZE TILEX * TILESIZE
//////////////////////////////////////////////////////


//////////////////////////////////////////////////////
/*

	�� / ���� ����

*/
//////////////////////////////////////////////
class frameObject;
class Citem;
// ����
// ���� Ÿ�� ����
#define SAMPLETILEX 18
#define SAMPLETILEY 14

// ������ ����� ���,  ���� �������� CRTL�� ���� �� Ÿ�� �Ӽ����� ���
#define TILESIZE  36		//���� Ÿ�� �̹��� ������
#define TILEX	  50		//�� Ÿ�� x�� ���� 
#define TILEY     50		//�� Ÿ�� y�� ����

#define TILESIZEX TILEX * TILESIZE	// �� Ÿ�� ��ü x�� ������(����)
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

//���� �Ӽ� ����
enum class TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_END
};

//������Ʈ �Ӽ� ����
//(ex : ���� ���ʿ�  ��ġ, �����̰ų� �μ����ų��ϴ� ��ȭ�� �ټ��ִ� ��ü)
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

//������ Ÿ�� ���� ���� �뵵
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

//Ÿ�� ����ü (�ʿ� �׸� Ÿ��)
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

//���� (����) Ÿ�� ����ü
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//���� Ÿ�� ����ü
struct tagCurrentTile
{
	int frame_x;
	int frame_y;

	OBJECTIMAGE terrainImage;
	OBJECTIMAGE objImage;
};

// �巡�� �ҽ� ���� Ÿ�� �ε��� x,y ���� �� Ÿ�� �ε��� x, y ����
struct tagDragTileIndex
{
	int index_StartX;
	int index_StartY;
	int index_EndX;
	int index_EndY;

	// ���� �ʿ��� �̿�
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

	�κ��丮, ������ ����

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

	���� ��� ������

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