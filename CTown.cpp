#include "framework.h"
#include "Ctown.h"
#include "camera.h"

Ctown::Ctown()
{
}

Ctown::~Ctown()
{
}

HRESULT Ctown::init()
{
    load();
	initTileAttribute();

    return S_OK;
}

void Ctown::release()
{
}

void Ctown::update()
{
}

void Ctown::render()
{
	this->cullingRender();

	if (!m_frameObject.empty())
	{
		for (auto iter = m_frameObject.begin(); iter != m_frameObject.end(); ++iter)
		{
			(*iter).frameObject->render();
		}
	}

	/*for (auto iter = m_fastLoadIndex.begin(); iter != m_fastLoadIndex.end(); ++iter)
	{
		IMAGE->frameRender("tilemap", getMapDC(), _tiles[(*iter).x + (*iter).y * TILEX].rc.left, _tiles[(*iter).x + (*iter).y * TILEX].rc.top, 0, 0);
	}*/
}

void Ctown::load()
{
    HANDLE file;
    DWORD read;

    file = CreateFile("townMap.map",
        GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, m_frameObjectInfo, sizeof(tagFrameObjectInfo) * TILEX * TILEY, &read, NULL);
    ReadFile(file, _tilesImage, sizeof(tagTileImage) * TILEX * TILEY, &read, NULL);
    ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
    ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
    CloseHandle(file);

	this->initFrameObject();
}

void Ctown::cullingRender()
{
	// Ÿ�� ���� ����ȭ
	// ī�޶� �»�� ��ǥ ���غ��� ���ϴ� ��ǥ������ Ÿ�� �ε����� �������ϰ� ����
	//int index_X1 = m_camera->getCameraPoint().x / TILESIZE;
	//int index_Y1 = m_camera->getCameraPoint().y / TILESIZE;
	//int index_X2 = m_camera->getCameraPoint2().x / TILESIZE;
	//int index_Y2 = m_camera->getCameraPoint2().y / TILESIZE;

	//int startX = index_X1;
	//int startY = index_Y1;
	//int endX = index_X2;
	//int endY = index_Y2;

	// �ε��� �����ʰ� ����ó��
	/*if (endY > 49)
		endY = 49;
	if (endX > 49)
		endX = 49;*/

	//for (int i=0; i< TILEX*TILEY; i++)
	//{
	//	IMAGE->frameRender(this->getImageName(_tilesImage[i].terrainImage), getTileDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

	//	if (_tiles[i].obj == OBJECT::OBJ_NONE)continue;
	//	IMAGE->frameRender(this->getImageName(_tilesImage[i].objImage), getTileDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	//}

	this->getTileBuffer()->render(getMapDC(), 0, 0);
}

void Ctown::initTileAttribute()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].collisionObj == COLLISIONOBJECT::COLLISIONOBJ) m_attribute[i] = ATTRIBUTE::COLLISION_ON;
		else m_attribute[i] = ATTRIBUTE::COLLISION_OFF;

		IMAGE->frameRender(this->getImageName(_tilesImage[i].terrainImage), getTileDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);

		if (_tiles[i].obj == OBJECT::OBJ_NONE)continue;
		IMAGE->frameRender(this->getImageName(_tilesImage[i].objImage), getTileDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);
	}

	/*for (int i = 0; i < TILEX; i++)
	{
		LineMake(getTileDC(), 0, i * TILESIZE, MAPSIZE, i * TILESIZE);
		LineMake(getTileDC(), i * TILESIZE, 0, i * TILESIZE, MAPSIZE);
	}*/
}

void Ctown::initFrameObject()
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

void Ctown::setFrameObject(int x, int y, KINDFRAMEOBJECT frameKind, int index)
{
	tagFrameObject tempObject;
	tempObject.frameObject = new frameObject;
	tempObject.frameObject->init(x, y, frameKind);
	tempObject.index = index;
	m_frameObject.push_back(tempObject);
}

string Ctown::getImageName(OBJECTIMAGE image)
{
	string imageStr;

	switch (image)
	{
	case OBJECTIMAGE::OBJECTIMAGE_TILE:
		imageStr = "tilemap1";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT1:
		imageStr = "������ƮŸ��1";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT2:
		imageStr = "������ƮŸ��2";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT3:
		imageStr = "������ƮŸ��3";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT4:
		imageStr = "������ƮŸ��4";
		break;
	case OBJECTIMAGE::OBJECTIMAGE_OBJECT5:
		imageStr = "������ƮŸ��5";
		break;
	}

	return imageStr;
}
