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
	sprintf_s(str, "서브타일 : %d ", m_subTile);
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
	// 맵 세팅 - rect 세팅!
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

	// 맵 세팅 - 타일 초기 속성 세팅!
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

	// 초기 타일 정보 뒤로가기용 리스트에 저장
	this->pushTile();
}

void mapToolMain::setMap()
{
	//마우스 좌표 보정!!!
	POINT cameraMouse = m_ptMouse;
	cameraMouse.x += m_camera->getCameraPoint().x;
	cameraMouse.y += m_camera->getCameraPoint().y;

	//맵 타일 세팅

	for (size_t i = 0; i < TILEX * TILEY; i++)
	{
		// 샘플 툴 쪽에서 눌렀을 때 맵 타일에 그려지지 않도록 카메라 범위 안에서만 타일 세팅 작동
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
					// 지우개
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
// 타일을 두번 클릭해서 두 타일 사이의 모든 타일을 채움
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
				// 타일이 비어있을땐 바로 push
				if (m_vSelectTileIndex.empty())
				{
					m_vSelectTileIndex.push_back(i);
					break;
				}
				// 타일이 한개 선택되어 있을 때
				else if (m_vSelectTileIndex.size() == 1)
				{
					if (m_vSelectTileIndex[0] == i)	// 같은 타일 선택일 경우 break;
						break;
					else
					{
						m_vSelectTileIndex.push_back(i);	// 다른 타일일 경우 push 및 그려주기 / 초기화

						int j, k;

						int startX, startY;
						int endX, endY;
						this->indexCalculate(m_vSelectTileIndex, &startX, &startY, &endX, &endY);
						// k는 선택된 타일 2개중 작은 인덱스 y 값
						// j는 선택된 타일 2개중 작은 인덱스 x 값
						for (k = startY; k <= endY; k++)
						{
							for (j = startX; j <= endX; j++)
							{
								// 그리려는 위치와 이미지가 다를시 체크변수값 ++, 체크변수가 0라면, 모두 동일한 것이라는 의미
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
						// m_isDifferentTile 변수를 사용하여, 뒤로가기에 저장할 타일에 대해 중복을 방지함!
						// ex) stayKeyDown으로 같은지점 계속 누르고 있는것들이 모두 뒤로가기 타일에 저장되면 안됨
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
	//시멘트
	if (frameX == 1 && frameY == 0)
	{
		return TERRAIN::TR_CEMENT;
	}
	//사막
	else if (frameX == 2 && frameY == 0)
	{
		return TERRAIN::TR_DESERT;
	}
	//잔디
	else if (frameX == 3 && frameY == 0)
	{
		return TERRAIN::TR_GRASS;
	}
	//잔디
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
		//return OBJECT::OBJ_BLOCKS; // 부서지지 않는 오브젝트(벽)
	}
	else if (frameX == 2 && frameY == 0)
	{
		return OBJECT::OBJ_BLOCK1; // 체력1인 오브젝트
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

// 뒤로가기용 푸쉬타일, 현재 타일 정보를 리스트에 저장해두고 나중에 불러오기
void mapToolMain::pushTile()
{
	tagTile* temp = new tagTile[TILEX * TILEY];
	tagTileImage* tempImg = new tagTileImage[TILEX * TILEY];

	memset(temp, 0, sizeof(tagTile) * TILEX * TILEY);
	memset(tempImg, 0, sizeof(tagTileImage) * TILEX * TILEY);

	setTile(temp, _tiles, tempImg, _tilesImage);

	m_lTileMemory.push_back(temp);
	m_lTileImageMemory.push_back(tempImg);

	// 기억할 타일 변경 정보는 100개 까지.. 일단
	if (m_lTileMemory.size() > 100)
	{
		// 할당받은거 해제 안하면 터짐..
		tagTile* temp2 = m_lTileMemory.front();
		m_lTileMemory.pop_front();
		SAFE_DELETE(temp2);
	}
	// 문제가 터지는곳
	if (m_lTileImageMemory.size() > 100)
	{
		// 예균이표 이터레이터 활용 코드.. but 버그는 여전함
		//auto tempImg2 = m_lTileImageMemory.begin();
		////delete[] *tempImg2;
		//m_lTileImageMemory.erase(tempImg2);
		tagTileImage* tempImg2 = m_lTileImageMemory.front();
		m_lTileImageMemory.pop_front();
		SAFE_DELETE(tempImg2); 

	}
}

// 뒤로가기용 셋 타일,  이전 타일 정보를 현재 타일에 대입
void mapToolMain::setTile(tagTile* tileDst, tagTile* tileSour, tagTileImage* tileImgDst, tagTileImage* tileImgSour)
{
	memcpy(tileDst, tileSour, sizeof(tagTile) * TILEX * TILEY);
	memcpy(tileImgDst, tileImgSour, sizeof(tagTileImage) * TILEX * TILEY);
}

void mapToolMain::indexCalculate(vector<int> vInt, int* x1, int* y1, int* x2, int* y2)
{
	int temp;
	// 크기 순서 정렬
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

	// 크기 순서 정렬
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
// 코드 간략화를 위한 함수

void mapToolMain::drawTerrain(int i)
{
	int j, k;
	int l, m;

	j = m_currentDragTile.index_StartY;
	l = m_currentDragTile.frame_StartY;

	// 그리기 시작할 인덱스 X,Y/ 끝 X,Y 와,  저장해둔 프레임 시작 인덱스 X,Y를 이용하여 범위로 그리기 구현
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
	// 이전과 같은 타일이 아닐때
	// m_isDifferentTile 변수를 사용하여, 뒤로가기에 저장할 타일에 대해 중복을 방지함!
	// ex) stayKeyDown으로 같은지점 계속 누르고 있는것들이 모두 뒤로가기 타일에 저장되면 안됨
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
	// 타일 랜더 최적화
	// 카메라 좌상단 좌표 기준부터 우하단 좌표까지를 타일 인덱스로 렌더링하게 구현
	int index_X1 = m_camera->getCameraPoint().x / TILESIZE;
	int index_Y1 = m_camera->getCameraPoint().y / TILESIZE;
	int index_X2 = m_camera->getCameraPoint2().x / TILESIZE;
	int index_Y2 = m_camera->getCameraPoint2().y / TILESIZE;

	int startX = index_X1;
	int startY = index_Y1;
	int endX = index_X2;
	int endY = index_Y2;

	// 인덱스 범위초과 예외처리
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
			//	_tilesImage[startX + startY * TILEX].objImage = "오브젝트타일1";
			if (_tiles[startX + startY * TILEX].obj == OBJECT::OBJ_NONE)continue;
			IMAGE->frameRender(this->getImageName(_tilesImage[startX + startY * TILEX].objImage), getMapDC(), _tiles[startX + startY * TILEX].rc.left, _tiles[startX + startY * TILEX].rc.top, _tiles[startX + startY * TILEX].objFrameX, _tiles[startX + startY * TILEX].objFrameY);

		}
	}
}
