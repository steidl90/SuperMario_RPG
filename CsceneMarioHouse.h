#pragma once
#include "gameNode.h"
#include "Chouse.h"
#include "CplayerManager.h"
class CsceneMarioHouse :public gameNode
{
private:
	Chouse* m_house;
	CplayerManager* m_playerM;

private:
	RECT m_door;

public:
	CsceneMarioHouse();
	~CsceneMarioHouse();

	HRESULT init();
	void release();
	void update();
	void render();

	void scenechange();
};

