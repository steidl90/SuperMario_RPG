#pragma once
#include "CmonsterFactory.h"
#include "Cunit.h"
class Cmario;
class CplayerManager;
class CmonsterManager:public Cunit
{
private:
	stats m_stats;
	CHARACTER_TYPE m_CollisionType;

	Cmonster* m_monster;
	Cmario* m_player;
	CplayerManager* m_playerBattle;

	vector<Cmonster*> vMonster;
	vector<Cmonster*>::iterator viMonster;

	float timer;
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
	void setPlayerBattleMemory(CplayerManager* playerbattle) { m_playerBattle = playerbattle; }

	Cmario* getPlayer() { return m_player; }
	vector<Cmonster*>* getVecMonster() { return &vMonster; }
	CHARACTER_TYPE getType() { return m_CollisionType; }
	//CFSMController* getMonsterFSM() { return m_FSM; }

	void vecClear() { vMonster.clear(); }
};

