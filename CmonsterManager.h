#pragma once
#include "CmonsterFactory.h"
#include "Cunit.h"
class Cmario;
class CmonsterManager:public Cunit
{
private:
	stats m_stats;
	CHARACTER_TYPE m_CollisionType;

	Cmonster* m_monster;
	Cmario* m_player;

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
	vector<Cmonster*>* getVecMonster() { return &vMonster; }
	CHARACTER_TYPE getType() { return m_CollisionType; }
	//CFSMController* getMonsterFSM() { return m_FSM; }

	void vecClear() { vMonster.clear(); }
};

