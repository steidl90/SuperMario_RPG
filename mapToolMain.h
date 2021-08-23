#pragma once
#include"gameNode.h"
#include"frameObject.h"
#include<list>
/*
	���� Ÿ�� �κ�
	�ʿ� �׷����� Ŭ�����Դϴ�
*/

class camera;
class mapToolMain : public gameNode
{
	typedef list<tagTile*> tileMemory;
	typedef list<tagTileImage*> tileImageMemory;
private:

	camera* m_camera;

	// �� Ÿ�Ͽ� �����ϴ� �浹 �Ӽ�
	ATTRIBUTE m_attribute[TILEX * TILEY];

	tagTile _tiles[TILEX * TILEY];

	tagTileImage _tilesImage[TILEX * TILEY]; // �� Ÿ�Ͽ� �����ϴ� �̹��� ������ ��� ����ü �迭

	tagFrameObjectInfo m_frameObjectInfo[TILEX * TILEY];	// ������Ʈ ������ Ŭ������ �ҷ����� ���� ����?

	vector<tagFrameObject> m_vFrameObject;	// ������ ��� ������ Ŭ�����鿡 ���� �����ϱ� ���� ������ Ŭ���� ������� ����, ���� ����

	KINDFRAMEOBJECT m_currentFrameKind; // ����, ����������� ���� ������ ������ ������Ʈ ���� ��� enum Ŭ����

	tagCurrentTile _currentTile; // ����, ����������� ���� ������ ���� Ÿ�� ���� ��� ����ü

	tagDragTileIndex m_currentDragTile; // ����,  ����������� ���� ������ ���� Ÿ�� ���� ��� ����ü

	int _ctrSelect; // ����,  ���õ� ���?

	int m_subTile; // ����������� ���õ� Ÿ�� �� �ѹ�? , ����

	tileMemory m_lTileMemory; // �ڷΰ��⸦ ����, ���� Ÿ�ϸ��� ������ �� �Ӽ� ������ ����ִ� ����Ʈ

	tileImageMemory m_lTileImageMemory; // �ڷΰ��⸦ ����, ���� Ÿ�ϸʿ��� �� Ÿ���� �̹��� ������ ����ִ� ����Ʈ

	vector<int> m_vSelectTileIndex; // ä��⸦ ����, ù ���� Ÿ�� x,y �ε���  �� ���� Ÿ�� x,y �ε����� ����ִ� ����


	bool m_isCollisionTileOn;

	// ��ư Ŭ�� ���� 
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

	// Ÿ�� �Ӽ� �ʱ�ȭ
	void initTileAttribute();

	// �̹��� �ҷ����� �Լ�
	string getImageName(OBJECTIMAGE image);

	// ������ ������Ʈ ���� �Լ�
	void setFrameObject(int x, int y, KINDFRAMEOBJECT frameKind, int index);
	void deleteFrameObject(int index);
	void initFrameObject();

	tagFrameObjectInfo* getFrameObjectInfo() { return m_frameObjectInfo; }

	// ���� ������ �޾ƿ���
	void setMainMapCurrentTile(tagCurrentTile tile) { _currentTile = tile; }
	void setMainMapDragTile(tagDragTileIndex tile) { m_currentDragTile = tile; }
	void setMainMapSelect(int select) { _ctrSelect = select; }
	void setSubTile(int sub) { m_subTile = sub; }
	void setFrameKind(KINDFRAMEOBJECT frameKind) { m_currentFrameKind = frameKind; }

	// �ڷΰ��� �������� �ʿ��� �Լ���
	void pushTile();
	void setTile(tagTile* tileDst, tagTile* tileSour, tagTileImage* tileImgDst, tagTileImage* tileImgSour);
	tileMemory* getMemoryTile() { return &m_lTileMemory; }
	tileImageMemory* getMemoryTileImage() { return &m_lTileImageMemory; }

	// �ε���

	void indexCalculate(vector<int> vInt, int* x1, int* y1, int* x2, int* y2);

	// �ڵ� ����ȭ�� ���� �Լ���

	void drawTerrain(int index);
	void drawObject(int index);
	void cullingRender();

	
};

