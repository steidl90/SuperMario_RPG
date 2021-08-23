#pragma once
#include"gameNode.h"
#include"frameObject.h"
#include<list>
/*
	왼쪽 타일 부분
	맵에 그려지는 클래스입니다
*/

class camera;
class mapToolMain : public gameNode
{
	typedef list<tagTile*> tileMemory;
	typedef list<tagTileImage*> tileImageMemory;
private:

	camera* m_camera;

	// 각 타일에 대응하는 충돌 속성
	ATTRIBUTE m_attribute[TILEX * TILEY];

	tagTile _tiles[TILEX * TILEY];

	tagTileImage _tilesImage[TILEX * TILEY]; // 각 타일에 대응하는 이미지 정보를 담는 구조체 배열

	tagFrameObjectInfo m_frameObjectInfo[TILEX * TILEY];	// 오브젝트 프레임 클래스들 불러오기 위한 정보?

	vector<tagFrameObject> m_vFrameObject;	// 생성된 모든 프레임 클래스들에 대해 접근하기 위한 프레임 클래스 정보담는 벡터, 실제 렌더

	KINDFRAMEOBJECT m_currentFrameKind; // 공용, 서브맵툴에서 현재 선택한 프레임 오브젝트 종류 담긴 enum 클래스

	tagCurrentTile _currentTile; // 공용, 서브맵툴에서 현재 선택한 단일 타일 정보 담긴 구조체

	tagDragTileIndex m_currentDragTile; // 공용,  서브맵툴에서 현재 선택한 범위 타일 정보 담긴 구조체

	int _ctrSelect; // 공용,  선택된 기능?

	int m_subTile; // 서브맵툴에서 선택된 타일 판 넘버? , 공용

	tileMemory m_lTileMemory; // 뒤로가기를 위한, 이전 타일맵의 프레임 및 속성 정보를 담고있는 리스트

	tileImageMemory m_lTileImageMemory; // 뒤로가기를 위한, 이전 타일맵에서 각 타일의 이미지 정보를 담고있는 리스트

	vector<int> m_vSelectTileIndex; // 채우기를 위한, 첫 선택 타일 x,y 인덱스  끝 선택 타일 x,y 인덱스를 담고있는 벡터


	bool m_isCollisionTileOn;

	// 버튼 클릭 여부 
	bool m_isButtonClick;

	int m_isDifferentTile;

public:

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);

	void maptoolSetup();
	void setMap();
	void fillMap();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);
	COLLISIONOBJECT collisionObjSelect(int frameX, int frameY);

	tagTile* getMainMapTile() { return _tiles; }
	tagTileImage* getMainMapTileImage() { return _tilesImage; }
	ATTRIBUTE* getAttribute() { return m_attribute; }

	void setCameraMemory(camera* c) { m_camera = c; }

	// 타일 속성 초기화
	void initTileAttribute();

	// 이미지 불러오기 함수
	string getImageName(OBJECTIMAGE image);

	// 프레임 오브젝트 관련 함수
	void setFrameObject(int x, int y, KINDFRAMEOBJECT frameKind, int index);
	void deleteFrameObject(int index);
	void initFrameObject();

	tagFrameObjectInfo* getFrameObjectInfo() { return m_frameObjectInfo; }

	// 공용 데이터 받아오기
	void setMainMapCurrentTile(tagCurrentTile tile) { _currentTile = tile; }
	void setMainMapDragTile(tagDragTileIndex tile) { m_currentDragTile = tile; }
	void setMainMapSelect(int select) { _ctrSelect = select; }
	void setSubTile(int sub) { m_subTile = sub; }
	void setFrameKind(KINDFRAMEOBJECT frameKind) { m_currentFrameKind = frameKind; }

	// 뒤로가기 구현위해 필요한 함수들
	void pushTile();
	void setTile(tagTile* tileDst, tagTile* tileSour, tagTileImage* tileImgDst, tagTileImage* tileImgSour);
	tileMemory* getMemoryTile() { return &m_lTileMemory; }
	tileImageMemory* getMemoryTileImage() { return &m_lTileImageMemory; }

	// 인덱스

	void indexCalculate(vector<int> vInt, int* x1, int* y1, int* x2, int* y2);

	// 코드 간략화를 위한 함수들

	void drawTerrain(int index);
	void drawObject(int index);
	void cullingRender();

	
};

