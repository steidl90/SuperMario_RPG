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

	int m_num;

public:
	CsceneBanditsWay();
	~CsceneBanditsWay();

	HRESULT init();
	HRESULT initBattle(int num);
	void release();
	void update();
	void render();

	void initMonster();

	void scenechange();

	int getNum() const { return m_num; }

	CmonsterManager* getMonsterManager() { return m_monsterM; }
};