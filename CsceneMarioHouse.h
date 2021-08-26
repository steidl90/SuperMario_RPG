#pragma once
#include "gameNode.h"
#include "Ccamera.h"
#include "Chouse.h"
#include "CplayerManager.h"
class CsceneMarioHouse :public gameNode
{
private:
	Ccamera* m_camera;
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

