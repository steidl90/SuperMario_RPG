#pragma once
#include "gameNode.h"
#include "CbanditsWay.h"
#include "CplayerManager.h"
#include "CmonsterManager.h"

class CsceneBanditsWay :public gameNode
{
private:
	CbanditsWay* m_banditsWay;
	CplayerManager* m_playerM;
	CmonsterManager* m_monsterM;
	
	CHARACTER_TYPE m_monsterType;

	vector<Cmonster*>::iterator m_viMonster;
private:
	RECT m_door;

public:
	CsceneBanditsWay();
	~CsceneBanditsWay();

	HRESULT init();
	void release();
	void update();
	void render();

	void initMonster();

	void scenechange();

	CmonsterManager* getMonsterManager() { return m_monsterM; }
};