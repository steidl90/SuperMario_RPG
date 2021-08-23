#include"framework.h"
#include "mapToolSub.h"
#include "mapToolMain.h"

HRESULT mapToolSub::init()
{

	maptoolSetup();
	m_subTile = 0;
	m_isKeyUp = true;
	isTileLine = false;
	return S_OK;
}

void mapToolSub::release()
{
}

void mapToolSub::update()
{
	//���� Ÿ�ϸ� �׸��� on off
	if (isTileLine)
	{
		for (int i = 0; i < TILEX; i++)
		{
			LineMake(getMapDC(), 0, i * TILESIZE, MAPSIZE, i * TILESIZE);
			LineMake(getMapDC(), i * TILESIZE, 0, i * TILESIZE, MAPSIZE);
		}
	}

	// �Է� ��� ����
	this->inputFunction();
	
	setMap();


	
}

void mapToolSub::render()
{
	//������ Ÿ�� �̹���
	if (m_subTile == 0)IMAGE->render("tilemap1", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth(), 0);
	if (m_subTile == 1)IMAGE->render("������ƮŸ��1", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��1")->getWidth(), 0);
	if (m_subTile == 2)IMAGE->render("������ƮŸ��2", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��2")->getWidth(), 0);
	if (m_subTile == 3)IMAGE->render("������ƮŸ��3", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��3")->getWidth(), 0);
	if (m_subTile == 4)IMAGE->render("������ƮŸ��4", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��4")->getWidth(), 0);
	if (m_subTile == 5)IMAGE->render("������ƮŸ��5", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��5")->getWidth(), 0);


	//������ Ÿ�� �׸���
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		LineMake(getMemDC(), MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth(), i * TILESIZE, MAPTOOLPOINT, i * TILESIZE);
	}
	for (int i = 0; i < SAMPLETILEX; i++)
	{
		LineMake(getMemDC(), MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth() + i * TILESIZE, 0, MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth() + i * TILESIZE, IMAGE->findImage("tilemap1")->getHeight());
	}
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 120, TEXT("�浹���찳    - L"), lstrlen("�浹���찳    - L"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 140, TEXT("���������찳    - ��Ʈ��+E"), lstrlen("���������찳    - ��Ʈ��+E"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 160, TEXT("����    - 1"), lstrlen("����    - 1"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 180, TEXT("������Ʈ    - 2"), lstrlen("������Ʈ    - 2"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 200, TEXT("���찳    - E"), lstrlen("���찳    - E"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 220, TEXT("���̺�    - ��Ʈ��+S"), lstrlen("���̺�    - ��Ʈ��+S"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 240, TEXT("�ε�    - ��Ʈ��+V"), lstrlen("�ε�    - ��Ʈ��+V"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 260, TEXT("ä���    - 3"), lstrlen("ä���    - 3"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 280, TEXT("�ڷΰ���    - ��Ʈ��+Z"), lstrlen("�ڷΰ���    - ��Ʈ��+Z"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 300, TEXT("Ÿ�ϸ� �׸���    - F1(on),F2(off)"), lstrlen("Ÿ�ϸ� �׸���    - F1(on),F2(off)"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 320, TEXT("����Ÿ�Ϻ���    - ����(Tab), �ڷ�(Ctrl+Tab)"), lstrlen("����Ÿ�Ϻ���    - ����(Tab), �ڷ�(Ctrl+Tab)"));

	this->clickAlphaRender();

	/*char str[1000];
	sprintf_s(str, "xxxx : %s", *m_mapToolmain->getMainMapTileImage()[10].objImage);
	TextOut(getMemDC(), 500, 500, str, lstrlen(str));*/
}

void mapToolSub::maptoolSetup()
{
	if (m_subTile == 0)_ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);
	//���� �� ���� ��� Ÿ�� �ε���
	for (size_t i = 0; i < SAMPLETILEY; i++)
	{
		for (size_t j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			//��Ʈ ����
			if (m_subTile == 0)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_TILE;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_TILE;

			}
			if (m_subTile == 1)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��1")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��1")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT1;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT1;
			}
			if (m_subTile == 2)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��2")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��2")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT2;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT2;
			}
			if (m_subTile == 3)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��3")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��3")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT3;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT3;
			}
			if (m_subTile == 4)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��4")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��4")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT4;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT4;
			}
			if (m_subTile == 5)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��5")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("������ƮŸ��5")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT5;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT5;
			}
		}
	}
}


// ������ Ÿ�� Ŭ����, Ÿ���� �̹��� ������ �������� current ����ü�� ��´�
// current ����ü�� main���� ���޵Ǿ Ÿ�� �׸��� ���
void mapToolSub::setMap()
{
	if (m_subTile == 0)
	{
		if (m_isButtonClick)
		{
			if (PtInRect(&_sampleTiles[0].rcTile, m_ptMouse))
			{
				_ctrSelect = static_cast<int>(CTRL::CTRL_COLLISIONTILE);
				m_isTileClick = true;
			}
		}
	}

	if (m_subTile == 1)
	{
		if (m_isButtonClick)
		{
			for (size_t i = 248; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse))
				{

					_ctrSelect = static_cast<int>(CTRL::CTRL_FRAME);
					if (i == 248)
						m_currentFrameKind = KINDFRAMEOBJECT::GRASS_BIG;
					if (i == 249)
						m_currentFrameKind = KINDFRAMEOBJECT::GRASS_SAMLL1;
					if (i == 250)
						m_currentFrameKind = KINDFRAMEOBJECT::GRASS_SMALL2;

					m_isTileClick = true;
					break;
				}
			}
		}
	}


	// ä��� ��� ������ ��ư Ŭ����
	if (_ctrSelect == static_cast<int>(CTRL::CTRL_FILL))
	{
		if (m_isButtonClick)
		{
			for (size_t i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
			{
				if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse))
				{
					_currentTile.frame_x = _sampleTiles[i].terrainFrameX;
					_currentTile.frame_y = _sampleTiles[i].terrainFrameY;
					_currentTile.terrainImage = _sampleTileImage[i].terrainImage;
					_currentTile.objImage = _sampleTileImage[i].objImage;
					m_isTileClick = true;
					break;
				}
			}
		}
	}
	else
	{
		//������ ���� Ŭ���ϴ� ����
		if (m_isButtonClick)
		{
			//ó�� ��Ŭ������ �¸� ȣ���� Ŭ�� �����ִµ��ȿ� ó�� �ѹ� Ÿ������ �Է¹ް� ���콺Ŭ��DOWN���� UP �ɶ� �ٽ� ���
			// ���º�ȭ�� ���� 1ȸ�� ����ǰ� �ϴ� keyUp ����
			if (m_isKeyUp)
			{
				for (size_t i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
				{
					if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse))
					{
						m_currentDragTile.index_StartX = _sampleTiles[i].terrainFrameX;
						m_currentDragTile.index_StartY = _sampleTiles[i].terrainFrameY;
						m_currentDragTile.terrainImage = _sampleTileImage[i].terrainImage;
						m_currentDragTile.objImage = _sampleTileImage[i].objImage;

						m_isKeyUp = false;
						break;
					}
				}
			}
		}
		// ��ư Ŭ���� false�� �Ǹ� -> ���콺 Ŭ�� ���� ����
		if (!m_isButtonClick)
		{
			// ���º�ȭ�� ���� 1ȸ�� ����ǰ� �ϴ� keyUp ����
			if (!m_isKeyUp)
			{
				for (size_t i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
				{
					if (PtInRect(&_sampleTiles[i].rcTile, m_ptMouse))
					{
						m_currentDragTile.index_EndX = _sampleTiles[i].terrainFrameX;
						m_currentDragTile.index_EndY = _sampleTiles[i].terrainFrameY;
						m_currentDragTile.terrainImage = _sampleTileImage[i].terrainImage;
						m_currentDragTile.objImage = _sampleTileImage[i].objImage;

						m_isTileClick = true;
						m_isKeyUp = true;

						// Ÿ�� ���� ũ�� ����
						if (m_currentDragTile.index_StartX > m_currentDragTile.index_EndX)
						{
							int temp;
							temp = m_currentDragTile.index_StartX;
							m_currentDragTile.index_StartX = m_currentDragTile.index_EndX;
							m_currentDragTile.index_EndX = temp;
						}

						if (m_currentDragTile.index_StartY > m_currentDragTile.index_EndY)
						{
							int temp;
							temp = m_currentDragTile.index_StartY;
							m_currentDragTile.index_StartY = m_currentDragTile.index_EndY;
							m_currentDragTile.index_EndY = temp;
						}

						this->dragTileInit();
						break;
					}
				}
			}
		}
	}
}

void mapToolSub::mapSave()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("tileMap.map",
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, m_mapToolmain->getFrameObjectInfo(), sizeof(tagFrameObjectInfo) * TILEX * TILEY, &write, NULL);
	WriteFile(file, m_mapToolmain->getMainMapTileImage(), sizeof(tagTileImage) * TILEX * TILEY, &write, NULL);
	WriteFile(file, m_mapToolmain->getMainMapTile(), sizeof(tagTile) * TILEX * TILEY, &write, NULL);
	WriteFile(file, _pos, sizeof(int) * 2, &write, NULL);
	CloseHandle(file);
}

void mapToolSub::mapLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("townMap.map",
		GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, m_mapToolmain->getFrameObjectInfo(), sizeof(tagFrameObjectInfo) * TILEX * TILEY, &read, NULL);
	ReadFile(file, m_mapToolmain->getMainMapTileImage(), sizeof(tagTileImage) * TILEX * TILEY, &read, NULL);
	ReadFile(file, m_mapToolmain->getMainMapTile(), sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);
	CloseHandle(file);

	// �ε��Ҷ� ���������� �ʱ�ȭ �ؾ��� �͵� �Լ� �ҷ��� ����

	m_mapToolmain->initFrameObject();
	m_mapToolmain->initTileAttribute();
}

void mapToolSub::dragTileInit()
{
	// ���� �ʿ��� Ÿ�Ͽ� ������ ������ x,y�� ����
	m_currentDragTile.frame_StartX = m_currentDragTile.index_StartX;
	m_currentDragTile.frame_StartY = m_currentDragTile.index_StartY;
	m_currentDragTile.frame_EndX = m_currentDragTile.index_EndX;
	m_currentDragTile.frame_EndY = m_currentDragTile.index_EndY;

	// ���� �ʿ��� Ÿ�Ͽ� �׷��ֱ� ���� �ε����� ����ϱ� ���� 0,0�� ���� x,y�� ����
	m_currentDragTile.index_StartX = m_currentDragTile.index_StartX - m_currentDragTile.frame_StartX;
	m_currentDragTile.index_StartY = m_currentDragTile.index_StartY - m_currentDragTile.frame_StartY;
	m_currentDragTile.index_EndX = m_currentDragTile.index_EndX - m_currentDragTile.frame_StartX;
	m_currentDragTile.index_EndY = m_currentDragTile.index_EndY - m_currentDragTile.frame_StartY;
}

// �ڵ� ����ȭ�� ���� �Լ���

void mapToolSub::inputFunction()
{
	// ��Ŭ��, �� ����
	if (InputManager->isStayKeyDown(VK_LBUTTON))
	{
		m_isButtonClick = true;
	}
	else
	{
		m_isButtonClick = false;
	}

	if (InputManager->isOnceKeyDown('1'))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);
	}
	else if (InputManager->isOnceKeyDown('2'))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_OBJDRAW);
	}
	else if (InputManager->isOnceKeyDown('E'))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_ERASER);
		memset(&m_currentDragTile, 0, sizeof(tagDragTileIndex));
	}
	else if (InputManager->isStayKeyDown(VK_CONTROL) && InputManager->isOnceKeyDown('E'))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_ERASERFRAME);
	}
	else if (InputManager->isStayKeyDown(VK_CONTROL) && InputManager->isOnceKeyDown('S'))
	{
		this->mapSave();
	}
	else if (InputManager->isStayKeyDown(VK_CONTROL) && InputManager->isOnceKeyDown('V'))
	{
		this->mapLoad();
	}
	else if (InputManager->isOnceKeyDown('3'))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_FILL);
	}
	else if (InputManager->isStayKeyDown(VK_CONTROL) && InputManager->isOnceKeyDown('Z'))
	{
		// �ڷΰ��� -> �����ص״� Ÿ�� ������ �ٽ� ����,  �����Ҵ���� Ÿ�� ��ȯ
		if (m_mapToolmain->getMemoryTile()->size() == 1)
		{
			m_mapToolmain->setTile(m_mapToolmain->getMainMapTile(), m_mapToolmain->getMemoryTile()->back(), m_mapToolmain->getMainMapTileImage(), m_mapToolmain->getMemoryTileImage()->back());
		}
		else
		{
			tagTile* temp2 = m_mapToolmain->getMemoryTile()->back();
			tagTileImage* tempImg2 = m_mapToolmain->getMemoryTileImage()->back();

			m_mapToolmain->getMemoryTile()->pop_back();
			m_mapToolmain->getMemoryTileImage()->pop_back();
			m_mapToolmain->setTile(m_mapToolmain->getMainMapTile(), m_mapToolmain->getMemoryTile()->back(), m_mapToolmain->getMainMapTileImage(), m_mapToolmain->getMemoryTileImage()->back());
			SAFE_DELETE(temp2);
			SAFE_DELETE(tempImg2);
		}
	}
	else if (InputManager->isStayKeyDown('L'))
	{
		_ctrSelect = static_cast<int>(CTRL::CTRL_ERASERCOLLISION);
	}


	// ���� Ÿ�� ��ȯ
	if (InputManager->isStayKeyDown(VK_CONTROL) && InputManager->isOnceKeyDown(VK_TAB)) // �ڷΰ���
	{
		if (m_subTile >= 0)m_subTile--;
		if (m_subTile < 0)m_subTile = 5;
		maptoolSetup();
	}
	if (InputManager->isOnceKeyDown(VK_TAB)) // �����ΰ���
	{
		if (m_subTile <= 5)m_subTile++;
		if (m_subTile > 5)m_subTile = 0;
		maptoolSetup();
	}

	//���� Ÿ�ϸ� �׸��� on off
	if (InputManager->isOnceKeyDown(VK_F1)) isTileLine = true;
	if (InputManager->isOnceKeyDown(VK_F2)) isTileLine = false;
}

void mapToolSub::clickAlphaRender()
{
	// ����Ÿ�� ���콺 Ŭ���� Ÿ�� �̹��� ���ķ���
	if (m_isTileClick && _ctrSelect != static_cast<int>(CTRL::CTRL_ERASER))
	{
		if (_ctrSelect == static_cast<int>(CTRL::CTRL_FILL))
		{
			if (m_subTile == 0)IMAGE->findImage("tilemap1")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 1)IMAGE->findImage("������ƮŸ��1")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 2)IMAGE->findImage("������ƮŸ��2")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 3)IMAGE->findImage("������ƮŸ��3")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 4)IMAGE->findImage("������ƮŸ��4")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 5)IMAGE->findImage("������ƮŸ��5")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
		}
		else
		{
			// �巡�׷� ���� ����
			int countI, i;
			int countJ, j;
			for (countI = 0, i = m_currentDragTile.frame_StartY; i <= m_currentDragTile.frame_EndY; countI++, i++)
			{
				for (countJ = 0, j = m_currentDragTile.frame_StartX; j <= m_currentDragTile.frame_EndX; countJ++, j++)
				{
					if (m_subTile == 0)IMAGE->findImage("tilemap1")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 1)IMAGE->findImage("������ƮŸ��1")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 2)IMAGE->findImage("������ƮŸ��2")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 3)IMAGE->findImage("������ƮŸ��3")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 4)IMAGE->findImage("������ƮŸ��4")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 5)IMAGE->findImage("������ƮŸ��5")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
				}
			}
		}
	}
}
