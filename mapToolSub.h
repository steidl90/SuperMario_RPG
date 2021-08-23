#pragma once
#include"gameNode.h"

/*
	������ Ÿ�� �κ�

	�̹����� �׸��� ���� �� Ŭ�����Դϴ�

*/

// ���� ������ Ÿ�� ���� �������� ���� ��������
class mapToolMain;

class mapToolSub : public gameNode
{
private:


	mapToolMain* m_mapToolmain;

	tagTileImage _sampleTileImage[SAMPLETILEX * SAMPLETILEY];

	tagSampleTile _sampleTiles[SAMPLETILEX * SAMPLETILEY];

	tagCurrentTile _currentTile; // ����

	KINDFRAMEOBJECT m_currentFrameKind; // ����

	tagDragTileIndex m_currentDragTile; // ����
	
	int _ctrSelect; // ����

	// ��ư Ŭ�� ���� 
	bool m_isButtonClick;
	// Ÿ�� Ŭ�� ����
	bool m_isTileClick;
	//��� �������� ���� Ű�� ����
	bool m_isKeyUp;
	int m_subTile; //������ Ÿ��

	bool isTileLine; //���� Ÿ�� �׸��� on off�뵵

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

	// ���� ������ �Լ�

	int getCtrlSelect()const { return _ctrSelect; }
	int getSubTile()const { return m_subTile; }
	tagCurrentTile getCurrentTile()const { return _currentTile; }
	tagDragTileIndex getTagDragTile()const { return m_currentDragTile; }
	KINDFRAMEOBJECT getFrameKind()const { return m_currentFrameKind; }

	// �ڵ� ����ȭ�� ���� �Լ���

	void inputFunction();
	void clickAlphaRender();
};

