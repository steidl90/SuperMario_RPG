#pragma once
#include "CmonsterFactory.h"
#include "CFSMController.h"
#include "Cunit.h"
class Cmario;
class CmonsterManager:public Cunit
{
private:
	stats m_stats;

	Cmonster* m_monster;
	Cmario* m_player;
	CFSMController* m_FSM;

	vector<Cmonster*> vMonster;
	vector<Cmonster*>::iterator viMonster;

public:
	CmonsterManager();
	~CmonsterManager();

	HRESULT init();
	HRESULT init(Cmario* player);
	void release();
	void update();
	void render();

	void attack();
	void move();

	void addMonster(CHARACTER_TYPE monster, float x, float y);

	void setPlayerMemory(Cmario* player) { m_player = player; }
	Cmario* getPlayer() { return m_player; }

	CFSMController* getMonsterFSM() { return m_FSM; }
	vector<Cmonster*> getVecMonster() { return vMonster; }
};

