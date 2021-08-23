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
	//왼쪽 타일맵 그리드 on off
	if (isTileLine)
	{
		for (int i = 0; i < TILEX; i++)
		{
			LineMake(getMapDC(), 0, i * TILESIZE, MAPSIZE, i * TILESIZE);
			LineMake(getMapDC(), i * TILESIZE, 0, i * TILESIZE, MAPSIZE);
		}
	}

	// 입력 명령 집합
	this->inputFunction();
	
	setMap();


	
}

void mapToolSub::render()
{
	//오른쪽 타일 이미지
	if (m_subTile == 0)IMAGE->render("tilemap1", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth(), 0);
	if (m_subTile == 1)IMAGE->render("오브젝트타일1", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("오브젝트타일1")->getWidth(), 0);
	if (m_subTile == 2)IMAGE->render("오브젝트타일2", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("오브젝트타일2")->getWidth(), 0);
	if (m_subTile == 3)IMAGE->render("오브젝트타일3", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("오브젝트타일3")->getWidth(), 0);
	if (m_subTile == 4)IMAGE->render("오브젝트타일4", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("오브젝트타일4")->getWidth(), 0);
	if (m_subTile == 5)IMAGE->render("오브젝트타일5", getMemDC(), MAPTOOLPOINT - IMAGE->findImage("오브젝트타일5")->getWidth(), 0);


	//오른쪽 타일 그리드
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		LineMake(getMemDC(), MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth(), i * TILESIZE, MAPTOOLPOINT, i * TILESIZE);
	}
	for (int i = 0; i < SAMPLETILEX; i++)
	{
		LineMake(getMemDC(), MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth() + i * TILESIZE, 0, MAPTOOLPOINT - IMAGE->findImage("tilemap1")->getWidth() + i * TILESIZE, IMAGE->findImage("tilemap1")->getHeight());
	}
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 120, TEXT("충돌지우개    - L"), lstrlen("충돌지우개    - L"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 140, TEXT("프레임지우개    - 컨트롤+E"), lstrlen("프레임지우개    - 컨트롤+E"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 160, TEXT("지형    - 1"), lstrlen("지형    - 1"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 180, TEXT("오브젝트    - 2"), lstrlen("오브젝트    - 2"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 200, TEXT("지우개    - E"), lstrlen("지우개    - E"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 220, TEXT("세이브    - 컨트롤+S"), lstrlen("세이브    - 컨트롤+S"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 240, TEXT("로드    - 컨트롤+V"), lstrlen("로드    - 컨트롤+V"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 260, TEXT("채우기    - 3"), lstrlen("채우기    - 3"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 280, TEXT("뒤로가기    - 컨트롤+Z"), lstrlen("뒤로가기    - 컨트롤+Z"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 300, TEXT("타일맵 그리드    - F1(on),F2(off)"), lstrlen("타일맵 그리드    - F1(on),F2(off)"));
	TextOut(getMemDC(), CAMERAWIDTH + 30, WINSIZEY / 2 + 320, TEXT("샘플타일변경    - 다음(Tab), 뒤로(Ctrl+Tab)"), lstrlen("샘플타일변경    - 다음(Tab), 뒤로(Ctrl+Tab)"));

	this->clickAlphaRender();

	/*char str[1000];
	sprintf_s(str, "xxxx : %s", *m_mapToolmain->getMainMapTileImage()[10].objImage);
	TextOut(getMemDC(), 500, 500, str, lstrlen(str));*/
}

void mapToolSub::maptoolSetup()
{
	if (m_subTile == 0)_ctrSelect = static_cast<int>(CTRL::CTRL_TERRAINDRAW);
	//샘플 맵 셋팅 모든 타일 인덱싱
	for (size_t i = 0; i < SAMPLETILEY; i++)
	{
		for (size_t j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			//렉트 생성
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
					(MAPTOOLPOINT - IMAGE->findImage("오브젝트타일1")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("오브젝트타일1")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT1;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT1;
			}
			if (m_subTile == 2)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("오브젝트타일2")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("오브젝트타일2")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT2;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT2;
			}
			if (m_subTile == 3)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("오브젝트타일3")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("오브젝트타일3")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT3;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT3;
			}
			if (m_subTile == 4)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("오브젝트타일4")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("오브젝트타일4")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT4;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT4;
			}
			if (m_subTile == 5)
			{
				SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
					(MAPTOOLPOINT - IMAGE->findImage("오브젝트타일5")->getWidth()) + j * TILESIZE,
					i * TILESIZE, (MAPTOOLPOINT - IMAGE->findImage("오브젝트타일5")->getWidth()) + j * TILESIZE + TILESIZE,
					i * TILESIZE + TILESIZE);

				_sampleTileImage[i * SAMPLETILEX + j].terrainImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT5;
				_sampleTileImage[i * SAMPLETILEX + j].objImage = OBJECTIMAGE::OBJECTIMAGE_OBJECT5;
			}
		}
	}
}


// 오른쪽 타일 클릭시, 타일의 이미지 프레임 정보등을 current 구조체에 담는다
// current 구조체는 main툴에 전달되어서 타일 그릴때 사용
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


	// 채우기 기능 선택후 버튼 클릭시
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
		//오른쪽 샘플 클릭하는 순간
		if (m_isButtonClick)
		{
			//처음 좌클릭으로 셋맵 호출후 클릭 눌려있는동안에 처음 한번 타일정보 입력받고 마우스클릭DOWN에서 UP 될때 다시 허용
			// 상태변화에 따라 1회만 실행되게 하는 keyUp 변수
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
		// 버튼 클릭이 false가 되면 -> 마우스 클릭 때는 순간
		if (!m_isButtonClick)
		{
			// 상태변화에 따라 1회만 실행되게 하는 keyUp 변수
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

						// 타일 숫자 크기 정렬
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

	// 로드할때 메인툴에서 초기화 해야할 것들 함수 불러다 쓰기

	m_mapToolmain->initFrameObject();
	m_mapToolmain->initTileAttribute();
}

void mapToolSub::dragTileInit()
{
	// 메인 맵에서 타일에 적용할 프레임 x,y값 설정
	m_currentDragTile.frame_StartX = m_currentDragTile.index_StartX;
	m_currentDragTile.frame_StartY = m_currentDragTile.index_StartY;
	m_currentDragTile.frame_EndX = m_currentDragTile.index_EndX;
	m_currentDragTile.frame_EndY = m_currentDragTile.index_EndY;

	// 메인 맵에서 타일에 그려주기 위한 인덱스를 계산하기 쉽게 0,0을 시작 x,y로 만듬
	m_currentDragTile.index_StartX = m_currentDragTile.index_StartX - m_currentDragTile.frame_StartX;
	m_currentDragTile.index_StartY = m_currentDragTile.index_StartY - m_currentDragTile.frame_StartY;
	m_currentDragTile.index_EndX = m_currentDragTile.index_EndX - m_currentDragTile.frame_StartX;
	m_currentDragTile.index_EndY = m_currentDragTile.index_EndY - m_currentDragTile.frame_StartY;
}

// 코드 간략화를 위한 함수들

void mapToolSub::inputFunction()
{
	// 좌클릭, 맵 셋팅
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
		// 뒤로가기 -> 저장해뒀던 타일 정보를 다시 대입,  동적할당받은 타일 반환
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


	// 샘플 타일 전환
	if (InputManager->isStayKeyDown(VK_CONTROL) && InputManager->isOnceKeyDown(VK_TAB)) // 뒤로가기
	{
		if (m_subTile >= 0)m_subTile--;
		if (m_subTile < 0)m_subTile = 5;
		maptoolSetup();
	}
	if (InputManager->isOnceKeyDown(VK_TAB)) // 앞으로가기
	{
		if (m_subTile <= 5)m_subTile++;
		if (m_subTile > 5)m_subTile = 0;
		maptoolSetup();
	}

	//왼쪽 타일맵 그리드 on off
	if (InputManager->isOnceKeyDown(VK_F1)) isTileLine = true;
	if (InputManager->isOnceKeyDown(VK_F2)) isTileLine = false;
}

void mapToolSub::clickAlphaRender()
{
	// 샘플타일 마우스 클릭시 타일 이미지 알파랜더
	if (m_isTileClick && _ctrSelect != static_cast<int>(CTRL::CTRL_ERASER))
	{
		if (_ctrSelect == static_cast<int>(CTRL::CTRL_FILL))
		{
			if (m_subTile == 0)IMAGE->findImage("tilemap1")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 1)IMAGE->findImage("오브젝트타일1")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 2)IMAGE->findImage("오브젝트타일2")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 3)IMAGE->findImage("오브젝트타일3")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 4)IMAGE->findImage("오브젝트타일4")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
			if (m_subTile == 5)IMAGE->findImage("오브젝트타일5")->alphaframeRender(getMemDC(), m_ptMouse.x - 10, m_ptMouse.y - 10, _currentTile.frame_x, _currentTile.frame_y, 128);
		}
		else
		{
			// 드래그로 범위 선택
			int countI, i;
			int countJ, j;
			for (countI = 0, i = m_currentDragTile.frame_StartY; i <= m_currentDragTile.frame_EndY; countI++, i++)
			{
				for (countJ = 0, j = m_currentDragTile.frame_StartX; j <= m_currentDragTile.frame_EndX; countJ++, j++)
				{
					if (m_subTile == 0)IMAGE->findImage("tilemap1")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 1)IMAGE->findImage("오브젝트타일1")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 2)IMAGE->findImage("오브젝트타일2")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 3)IMAGE->findImage("오브젝트타일3")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 4)IMAGE->findImage("오브젝트타일4")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
					if (m_subTile == 5)IMAGE->findImage("오브젝트타일5")->alphaframeRender(getMemDC(), m_ptMouse.x + countJ * TILESIZE, m_ptMouse.y + countI * TILESIZE, j, i, 128);
				}
			}
		}
	}
}
