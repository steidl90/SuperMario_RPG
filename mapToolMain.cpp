#include "framework.h"
#include "mapToolMain.h"
#include "mapToolSub.h"
#include "camera.h"

HRESULT mapToolMain::init()
{
	maptoolSetup();
	m_isDifferentTile = 0;
	m_subTile = 0;
	memset(&m_frameObjectInfo, 0, sizeof(tagFrameObjectInfo));
	return S_OK;
}

void mapToolMain::release()
{
}

void mapToolMain::update()
{
	if (InputManager->isStayKeyDown(VK_LBUTTON))
	{
		setMap();
		m_isButtonClick = true;
	}
	else
	{
		m_isButtonClick = false;
	}

	if (_ctrSelect == static_cast<int>(CTRL::CTRL_FILL))
	{
		if (InputManager->isOnceKeyDown(VK_LBUTTON))
			this->fillMap();
	}

	//if (InputManager->isStayKeyDown(VK_RBUTTON))
	//{
	//	if (!m_frameObject.empty())
	//	{
	//		for (auto iter = m_frameObject.begin(); iter != m_frameObject.end();)
	//		{
	//			if (PtInRect(&(*iter)->getRect(), m_ptMouse))
	//			{
	//				iter = m_frameObject.erase(iter);
	//			}
	//			else
	//			{
	//				++iter;
	//			}
	//		}
	//	}
	//}
}

void mapToolMain::render()
{
	
	this->cullingRender();

	char str[100];
	sprintf_s(str, "����Ÿ�� : %d ", m_subTile);
	TextOut(getMemDC(), 100, 100, str, lstrlen(str));

	if (!m_vFrameObject.empty())
	{
		for (auto iter = m_vFrameObject.begin(); iter != m_vFrameObject.end(); ++iter)
		{
			(*iter).frameObject->render();
		}
	}

	/*char str[1000];
	sprintf_s(str, "xxxx : %s", *_tilesImage[10].objImage);
	TextOut(getMemDC(), 500, 550, str, lstrlen(str));*/
}

void mapToolMain::maptoolSetup()
{
	// �� ���� - rect ����!
	for (size_t i = 0; i < TILEY; i++)
	{
		for (size_t j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	// �� ���� - Ÿ�� �ʱ� �Ӽ� ����!
	for (size_t i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 7;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameX = 0;

		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJECT::OBJ_NONE;
		
		_tilesImage[i].terrainImage = OBJECTIMAGE::OBJECTIMAGE_TILE;
		_tilesImage[i].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT1;
	}

	// �ʱ� Ÿ�� ���� �ڷΰ���� ����Ʈ�� ����
	this->pushTile();
}

void mapToolMain::setMap()
{
	//���콺 ��ǥ ����!!!
	POINT cameraMouse = m_ptMouse;
	cameraMouse.x += m_camera->getCameraPoint().x;
	cameraMouse.y += m_camera->getCameraPoint().y;

	//�� Ÿ�� ����

	for (size_t i = 0; i < TILEX * TILEY; i++)
	{
		// ���� �� �ʿ��� ������ �� �� Ÿ�Ͽ� �׷����� �ʵ��� ī�޶� ���� �ȿ����� Ÿ�� ���� �۵�
		if (m_camera->getCameraPoint().x <= _tiles[i].rc.left && m_camera->getCameraPoint().y <= _tiles[i].rc.top &&
			m_camera->getCameraPoint2().x >= _tiles[i].rc.right && m_camera->getCameraPoint2().y >= _tiles[i].rc.bottom)
		{
			if (PtInRect(&_tiles[i].rc, cameraMouse))
			{
				switch ((CTRL)_ctrSelect)
				{
				case CTRL::CTRL_TERRAINDRAW:
					this->drawTerrain(i); break;

				case CTRL::CTRL_OBJDRAW:
					this->drawObject(i); break;

				case CTRL::CTRL_FILL:
					break;
				case CTRL::CTRL_FRAME:
					m_frameObjectInfo[i].check = 1;
					m_frameObjectInfo[i].frame_kind = m_currentFrameKind;
					setFrameObject(_tiles[i].rc.left, _tiles[i].rc.top, m_currentFrameKind, i);
					break;
				case CTRL::CTRL_ERASERFRAME:
					m_frameObjectInfo[i].check = 0;
					m_frameObjectInfo[i].frame_kind = KINDFRAMEOBJECT::NONE;
					deleteFrameObject(i);
					break;
				default:
					// ���찳
					if (_tiles[i].obj != OBJECT::OBJ_NONE)
						m_isDifferentTile++;
					_tiles[i].obj = OBJECT::OBJ_NONE;
					if (m_isDifferentTile > 0)
					{
						this->pushTile();
						m_isDifferentTile = 0;
					}
					break;
				}
				InvalidateRect(m_hWnd, NULL, false);
				break;
			}

		}
	}

}
// Ÿ���� �ι� Ŭ���ؼ� �� Ÿ�� ������ ��� Ÿ���� ä��
void mapToolMain::fillMap()
{
	POINT cameraMouse = m_ptMouse;
	cameraMouse.x += m_camera->getCameraPoint().x;
	cameraMouse.y += m_camera->getCameraPoint().y;

	for (size_t i = 0; i < TILEX * TILEY; i++)
	{
		if (m_camera->getCameraPoint().x <= _tiles[i].rc.left && m_camera->getCameraPoint().y <= _tiles[i].rc.top &&
			m_camera->getCameraPoint2().x >= _tiles[i].rc.right && m_camera->getCameraPoint2().y >= _tiles[i].rc.bottom)
		{
			if (PtInRect(&_tiles[i].rc, cameraMouse))
			{
				// Ÿ���� ��������� �ٷ� push
				if (m_vSelectTileIndex.empty())
				{
					m_vSelectTileIndex.push_back(i);
					break;
				}
				// Ÿ���� �Ѱ� ���õǾ� ���� ��
				else if (m_vSelectTileIndex.size() == 1)
				{
					if (m_vSelectTileIndex[0] == i)	// ���� Ÿ�� ������ ��� break;
						break;
					else
					{
						m_vSelectTileIndex.push_back(i);	// �ٸ� Ÿ���� ��� push �� �׷��ֱ� / �ʱ�ȭ

						int j, k;

						int startX, startY;
						int endX, endY;
						this->indexCalculate(m_vSelectTileIndex, &startX, &startY, &endX, &endY);
						// k�� ���õ� Ÿ�� 2���� ���� �ε��� y ��
						// j�� ���õ� Ÿ�� 2���� ���� �ε��� x ��
						for (k = startY; k <= endY; k++)
						{
							for (j = startX; j <= endX; j++)
							{
								// �׸����� ��ġ�� �̹����� �ٸ��� üũ������ ++, üũ������ 0���, ��� ������ ���̶�� �ǹ�
								if (_tiles[j + k * TILEX].terrainFrameX != _currentTile.frame_x)
									m_isDifferentTile++;
								else if (_tiles[j + k * TILEX].terrainFrameY != _currentTile.frame_y)
									m_isDifferentTile++;
								else if (_tiles[j + k * TILEX].terrain != terrainSelect(1, 0))
									m_isDifferentTile++;

								_tiles[j + k * TILEX].terrainFrameX = _currentTile.frame_x;
								_tiles[j + k * TILEX].terrainFrameY = _currentTile.frame_y;
								_tiles[j + k * TILEX].terrain = terrainSelect(1, 0);
								_tilesImage[j + k * TILEX].terrainImage = _currentTile.terrainImage;
							}
						}
						// m_isDifferentTile ������ ����Ͽ�, �ڷΰ��⿡ ������ Ÿ�Ͽ� ���� �ߺ��� ������!
						// ex) stayKeyDown���� �������� ��� ������ �ִ°͵��� ��� �ڷΰ��� Ÿ�Ͽ� ����Ǹ� �ȵ�
						if (m_isDifferentTile > 0)
						{
							this->pushTile();
							m_isDifferentTile = 0;
						}
						m_vSelectTileIndex.clear();
						break;
					}
				}
				InvalidateRect(m_hWnd, NULL, false);
				break;
			}
		}
	}
}

TERRAIN mapToolMain::terrainSelect(int frameX, int frameY)
{
	//�ø�Ʈ
	if (frameX == 1 && frameY == 0)
	{
		return TERRAIN::TR_CEMENT;
	}
	//�縷
	else if (frameX == 2 && frameY == 0)
	{
		return TERRAIN::TR_DESERT;
	}
	//�ܵ�
	else if (frameX == 3 && frameY == 0)
	{
		return TERRAIN::TR_GRASS;
	}
	//�ܵ�
	else if (frameX == 4 && frameY == 0)
	{
		return TERRAIN::TR_WATER;
	}
	return TERRAIN::TR_GRASS;
}

OBJECT mapToolMain::objSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0)
	{
		//return OBJECT::OBJ_BLOCKS; // �μ����� �ʴ� ������Ʈ(��)
	}
	else if (frameX == 2 && frameY == 0)
	{
		return OBJECT::OBJ_BLOCK1; // ü��1�� ������Ʈ
	}
}

void mapToolMain::initTileAttribute()
{
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].collisionObj == COLLISIONOBJECT::COLLISIONOBJ)
		{
			m_attribute[i] = ATTRIBUTE::COLLISION_ON;
		}
		else
		{
			m_attribute[i] = ATTRIBUTE::COLLISION_OFF;
		}
	}
}

string mapToolMain::getImageName(OBJECTIMAGE image)
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

void mapToolMain::setFrameObject(int x, int y, KINDFRAMEOBJECT frameKind, int index)
{

	tagFrameObject tempObject;
	tempObject.frameObject = new frameObject;
	tempObject.frameObject->init(x, y, frameKind);
	tempObject.index = index;
	m_vFrameObject.push_back(tempObject);

}

void mapToolMain::deleteFrameObject(int index)
{
	if (!m_vFrameObject.empty())
	{
		for (auto iter = m_vFrameObject.begin(); iter != m_vFrameObject.end(); ++iter)
		{
			if ((*iter).index == index)
			{
				SAFE_DELETE((*iter).frameObject);
				m_vFrameObject.erase(iter);
				break;
			}
		}
	}
}

void mapToolMain::initFrameObject()
{
	m_vFrameObject.clear();
	for (size_t i = 0; i < TILEX * TILEY; i++)
	{
		if (m_frameObjectInfo[i].check == 1)
		{
			this->setFrameObject(_tiles[i].rc.left, _tiles[i].rc.top, m_frameObjectInfo[i].frame_kind, i);
		}
	}

	int temp = 10;
}

// �ڷΰ���� Ǫ��Ÿ��, ���� Ÿ�� ������ ����Ʈ�� �����صΰ� ���߿� �ҷ�����
void mapToolMain::pushTile()
{
	tagTile* temp = new tagTile[TILEX * TILEY];
	tagTileImage* tempImg = new tagTileImage[TILEX * TILEY];

	memset(temp, 0, sizeof(tagTile) * TILEX * TILEY);
	memset(tempImg, 0, sizeof(tagTileImage) * TILEX * TILEY);

	setTile(temp, _tiles, tempImg, _tilesImage);

	m_lTileMemory.push_back(temp);
	m_lTileImageMemory.push_back(tempImg);

	// ����� Ÿ�� ���� ������ 100�� ����.. �ϴ�
	if (m_lTileMemory.size() > 100)
	{
		// �Ҵ������ ���� ���ϸ� ����..
		tagTile* temp2 = m_lTileMemory.front();
		m_lTileMemory.pop_front();
		SAFE_DELETE(temp2);
	}
	// ������ �����°�
	if (m_lTileImageMemory.size() > 100)
	{
		// ������ǥ ���ͷ����� Ȱ�� �ڵ�.. but ���״� ������
		//auto tempImg2 = m_lTileImageMemory.begin();
		////delete[] *tempImg2;
		//m_lTileImageMemory.erase(tempImg2);
		tagTileImage* tempImg2 = m_lTileImageMemory.front();
		m_lTileImageMemory.pop_front();
		SAFE_DELETE(tempImg2); 

	}
}

// �ڷΰ���� �� Ÿ��,  ���� Ÿ�� ������ ���� Ÿ�Ͽ� ����
void mapToolMain::setTile(tagTile* tileDst, tagTile* tileSour, tagTileImage* tileImgDst, tagTileImage* tileImgSour)
{
	memcpy(tileDst, tileSour, sizeof(tagTile) * TILEX * TILEY);
	memcpy(tileImgDst, tileImgSour, sizeof(tagTileImage) * TILEX * TILEY);
}

void mapToolMain::indexCalculate(vector<int> vInt, int* x1, int* y1, int* x2, int* y2)
{
	int temp;
	// ũ�� ���� ����
	if (vInt[0] > vInt[1])
	{
		temp = vInt[0];
		vInt[0] = vInt[1];
		vInt[1] = temp;
	}

	*x1 = vInt[0] % TILEX;
	*y1 = vInt[0] / TILEX;
	*x2 = vInt[1] % TILEX;
	*y2 = vInt[1] / TILEX;

	// ũ�� ���� ����
	if (*x1 > *x2)
	{
		temp = *x1;
		*x1 = *x2;
		*x2 = temp;
	}
	if (*y1 > *y2)
	{
		temp = *y1;
		*y1 = *y2;
		*y2 = temp;
	}
}
// �ڵ� ����ȭ�� ���� �Լ�

void mapToolMain::drawTerrain(int i)
{
	int j, k;
	int l, m;

	j = m_currentDragTile.index_StartY;
	l = m_currentDragTile.frame_StartY;

	// �׸��� ������ �ε��� X,Y/ �� X,Y ��,  �����ص� ������ ���� �ε��� X,Y�� �̿��Ͽ� ������ �׸��� ����
	for ( ;j <= m_currentDragTile.index_EndY; j++, l++)
	{
		for (k = m_currentDragTile.index_StartX, m = m_currentDragTile.frame_StartX; k <= m_currentDragTile.index_EndX; k++, m++)
		{
			if (_tiles[i + k + j * TILEX].terrainFrameX != m)
				m_isDifferentTile++;
			else if (_tiles[i + k + j * TILEX].terrainFrameY != l)
				m_isDifferentTile++;
			else if (_tiles[i + k + j * TILEX].terrain != terrainSelect(1, 0))
				m_isDifferentTile++;

			_tiles[i + k + j * TILEX].terrainFrameX = m;
			_tiles[i + k + j * TILEX].terrainFrameY = l;
			_tiles[i + k + j * TILEX].terrain = terrainSelect(1, 0);
			_tilesImage[i + k + j * TILEX].terrainImage = m_currentDragTile.terrainImage;

		}
	}
	// ������ ���� Ÿ���� �ƴҶ�
	// m_isDifferentTile ������ ����Ͽ�, �ڷΰ��⿡ ������ Ÿ�Ͽ� ���� �ߺ��� ������!
	// ex) stayKeyDown���� �������� ��� ������ �ִ°͵��� ��� �ڷΰ��� Ÿ�Ͽ� ����Ǹ� �ȵ�
	if (m_isDifferentTile > 0)
	{
		this->pushTile();
		m_isDifferentTile = 0;
	}
}

void mapToolMain::drawObject(int i)
{
	int j, k;
	int l, m;
	for (j = m_currentDragTile.index_StartY, l = m_currentDragTile.frame_StartY; j <= m_currentDragTile.index_EndY; j++, l++)
	{
		for (k = m_currentDragTile.index_StartX, m = m_currentDragTile.frame_StartX; k <= m_currentDragTile.index_EndX; k++, m++)
		{
			if (_tiles[i + k + j * TILEX].objFrameX != m)
				m_isDifferentTile++;
			else if (_tiles[i + k + j * TILEX].objFrameY != l)
				m_isDifferentTile++;
			else if (_tiles[i + k + j * TILEX].obj != objSelect(1, 0))
				m_isDifferentTile++;

			_tiles[i + k + j * TILEX].objFrameX = m;
			_tiles[i + k + j * TILEX].objFrameY = l;
			_tiles[i + k + j * TILEX].obj = objSelect(1, 0);
			_tilesImage[i + k + j * TILEX].objImage = m_currentDragTile.objImage;
		}
	}
	if (m_isDifferentTile > 0)
	{
		this->pushTile();
		m_isDifferentTile = 0;
	}
}

void mapToolMain::cullingRender()
{
	// Ÿ�� ���� ����ȭ
	// ī�޶� �»�� ��ǥ ���غ��� ���ϴ� ��ǥ������ Ÿ�� �ε����� �������ϰ� ����
	int index_X1 = m_camera->getCameraPoint().x / TILESIZE;
	int index_Y1 = m_camera->getCameraPoint().y / TILESIZE;
	int index_X2 = m_camera->getCameraPoint2().x / TILESIZE;
	int index_Y2 = m_camera->getCameraPoint2().y / TILESIZE;

	int startX = index_X1;
	int startY = index_Y1;
	int endX = index_X2;
	int endY = index_Y2;

	// �ε��� �����ʰ� ����ó��
	if (endY > 49)
		endY = 49;
	if (endX > 49)
		endX = 49;

	for (startY = index_Y1; startY <= endY; startY++)
	{
		for (startX = index_X1; startX <= endX; startX++)
		{	
			//if (_tilesImage[startX + startY * TILEX].terrainImage == NULL)
			//	_tilesImage[startX + startY * TILEX].terrainImage = "tilemap";
			IMAGE->frameRender(this->getImageName(_tilesImage[startX + startY * TILEX].terrainImage), getMapDC(), _tiles[startX + startY * TILEX].rc.left, _tiles[startX + startY * TILEX].rc.top, _tiles[startX + startY * TILEX].terrainFrameX, _tiles[startX + startY * TILEX].terrainFrameY);

			//if (_tilesImage[startX + startY * TILEX].objImage == "")
			//	_tilesImage[startX + startY * TILEX].objImage = "������ƮŸ��1";
			if (_tiles[startX + startY * TILEX].obj == OBJECT::OBJ_NONE)continue;
			IMAGE->frameRender(this->getImageName(_tilesImage[startX + startY * TILEX].objImage), getMapDC(), _tiles[startX + startY * TILEX].rc.left, _tiles[startX + startY * TILEX].rc.top, _tiles[startX + startY * TILEX].objFrameX, _tiles[startX + startY * TILEX].objFrameY);

		}
	}
}
