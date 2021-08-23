#include "framework.h"
#include "Cdungeon.h"
#include "camera.h"

Cdungeon::Cdungeon()
{
}

Cdungeon::~Cdungeon()
{
}

HRESULT Cdungeon::init()
{
    load();
	initTileAttribute();
    return S_OK;
}

// 에이스타 초기화용

void Cdungeon::release()
{
}

void Cdungeon::update()
{
}

void Cdungeon::render()
{
	this->cullingRender();

	if (!m_frameObject.empty())
	{
		for (auto iter = m_frameObject.begin(); iter != m_frameObject.end(); ++iter)
		{
			(*iter).frameObject->render();
		}
	}

	/*for (int i = 0; i < TILEX; i++)
	{
		LineMake(getTileDC(), 0, i * TILESIZE, MAPSIZE, i * TILESIZE);
		LineMake(getTileDC(), i * TILESIZE, 0, i * TILESIZE, MAPSIZE);
	}*/
}

void Cdungeon::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("dungeon.map",
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, m_frameObjectInfo, sizeof(tagFrameObjectInfo) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _tilesImage, sizeof(tagTileImage) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);

	this->initFrameObject();
}

void Cdungeon::cullingRender()
{
	//// 타일 랜더 최적화
	//// 카메라 좌상단 좌표 기준부터 우하단 좌표까지를 타일 인덱스로 렌더링하게 구현
	//int index_X1 = m_camera->getCameraPoint().x / TILESIZE;
	//int index_Y1 = m_camera->getCameraPoint().y / TILESIZE;
	//int index_X2 = m_camera->getCameraPoint2().x / TILESIZE;
	//int index_Y2 = m_camera->getCameraPoint2().y / TILESIZE;

	//int startX = index_X1;
	//int startY = index_Y1;
	//int endX = index_X2;
	//int endY = index_Y2;

	//for (startY = index_Y1; startY <= endY; startY++)
	//{
	//	for (startX = index_X1; startX <= endX; startX++)
	//	{
	//		IMAGE->frameRender(this->getImageName(_tilesImage[startX + startY * TILEX].terrainImage), getMapDC(), _tiles[startX + startY * TILEX].rc.left, _tiles[startX + startY * TILEX].rc.top, _tiles[startX + startY * TILEX].terrainFrameX, _tiles[startX + startY * TILEX].terrainFrameY);

	//		if (_tiles[startX + startY * TILEX].obj == OBJECT::OBJ_NONE)continue;
	//		IMAGE->frameRender(this->getImageName(_tilesImage[startX + startY * TILEX].objImage), getMapDC(), _tiles[startX + startY * TILEX].rc.left, _tiles[startX + startY * TILEX].rc.top, _tiles[startX + startY * TILEX].objFrameX, _tiles[startX + startY * TILEX].objFrameY);
	//	}
	//}
	this->getTileBuffer()->render(getMapDC(), 0, 0);
}


void Cdungeon::initTileAttribute()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].collisionObj == COLLISIONOBJECT::COLLISIONOBJ) m_attribute[i] = ATTRIBUTE::COLLISION_ON;
		else m_attribute[i] = ATTRIBUTE::COLLISION_OFF;

		IMAGE->frameRender(this->getImageName(_tilesImage[i].terrainImage), getTileDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		if (_tiles[i].obj == OBJECT::OBJ_NONE)continue;
		IMAGE->frameRender(this->getImageName(_tilesImage[i].objImage), getTileDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}

void Cdungeon::initFrameObject()
{
	m_frameObject.clear();
	for (size_t i = 0; i < TILEX * TILEY; i++)
	{
		if (m_frameObjectInfo[i].check == 1)
		{
			this->setFrameObject(_tiles[i].rc.left, _tiles[i].rc.top, m_frameObjectInfo[i].frame_kind, i);
		}
	}
}

void Cdungeon::setFrameObject(int x, int y, KINDFRAMEOBJECT frameKind, int index)
{
	tagFrameObject tempObject;
	tempObject.frameObject = new frameObject;
	tempObject.frameObject->init(x, y, frameKind);
	tempObject.index = index;
	m_frameObject.push_back(tempObject);
}

string Cdungeon::getImageName(OBJECTIMAGE image)
{
	string imageStr;
	switch (image)
	{
	case OBJECTIMAGE::OBJECTIMAGE_TILE:
		imageStr = "tilemap";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT1:
		imageStr = "오브젝트타일1";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT2:
		imageStr = "오브젝트타일2";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT3:
		imageStr = "오브젝트타일3";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT4:
		imageStr = "오브젝트타일4";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT5:
		imageStr = "오브젝트타일5";
		break;
	}
	return imageStr;
}
