#pragma once
#include"gameNode.h"

/*
	오른쪽 타일 부분

	이미지로 그리기 위한 툴 클래스입니다

*/

// 메인 맵툴의 타일 정보 가져오기 위한 전방참조
class mapToolMain;

class mapToolSub : public gameNode
{
private:


	mapToolMain* m_mapToolmain;

	tagTileImage _sampleTileImage[SAMPLETILEX * SAMPLETILEY];

	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];

	tagCurrentTile _currentTile; // 공용

	KINDFRAMEOBJECT m_currentFrameKind; // 공용

	tagDragTileIndex m_currentDragTile; // 공용
	
	int _ctrSelect; // 공용

	// 버튼 클릭 여부 
	bool m_isButtonClick;
	// 타일 클릭 여부
	bool m_isTileClick;
	//토글 느낌으로 쓰는 키업 변수
	bool m_isKeyUp;
	int m_subTile; //오른쪽 타일

	bool isTileLine; //왼쪽 타일 그리드 on off용도

	int _pos[2];

	RECT _terrain;
	RECT _object;
	RECT _erase;
	RECT _save;
	RECT _load;
	RECT m_fill;
	RECT m_back;

public:

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void maptoolSetup();
	void setMap();

	void mapSave();
	void mapLoad();

	void dragTileInit();
	void setMapToolMainMemory(mapToolMain* mt) { m_mapToolmain = mt; }

	// 공용 데이터 함수

	int getCtrlSelect()const { return _ctrSelect; }
	int getSubTile()const { return m_subTile; }
	tagCurrentTile getCurrentTile()const { return _currentTile; }
	tagDragTileIndex getTagDragTile()const { return m_currentDragTile; }
	KINDFRAMEOBJECT getFrameKind()const { return m_currentFrameKind; }

	// 코드 간략화를 위한 함수들

	void inputFunction();
	void clickAlphaRender();
};

