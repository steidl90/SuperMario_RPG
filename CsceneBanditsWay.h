#pragma once
#include "gameNode.h"
#include "Ccamera.h"
#include "CbanditsWay.h"
#include "CplayerManager.h"
#include "CmonsterFactory.h"
class CsceneBanditsWay :public gameNode
{
private:
	Ccamera* m_camera;
	CbanditsWay* m_banditsWay;
	CplayerManager* m_playerM;

	Cmonster* m_goomba;
	Cmonster* m_skytroopa;

	vector<Cmonster*> vMonster;
	vector<Cmonster*>::iterator viMonster;

private:
	RECT m_door;

public:
	CsceneBanditsWay();
	~CsceneBanditsWay();

	HRESULT init();
	void release();
	void update();
	void render();

	void scenechange();
};