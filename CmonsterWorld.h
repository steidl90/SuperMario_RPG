#pragma once
#include "Cmonster.h"

class Cmario;
class CmarioBattle;
class CpeachBattle;
class CbowserBattle;
class CFSMController;
class CmonsterWorld :public Cmonster
{
private:
	animation* m_ani;
	CHARACTER_TYPE m_type;
	CFSMController* m_FSM;
	MONSTER_MOVE_TYPE m_moveType;
	Cmario* m_player;
	CmarioBattle* m_playerBattle;
	CpeachBattle* m_peachBattle;
	CbowserBattle* m_bowserBattle;

	char str[20];

public:
	CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type);
	CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type, Cmario* player);
	CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type, CmarioBattle* m_playerBattle);
	virtual ~CmonsterWorld() = default;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	//virtual void render(MONSTER_TYPE type);

	virtual void attack();
	virtual void move();

	void moveAi();
	void attackAi();

	void setGoombaStats();
	void setSkyTroopbStats();
	void setSpikeyStats();

	bool getIsDie() { return m_isDie; }
	void setIsDie(bool die) { m_isDie = die; }

	CFSMController* getMonsterFSM() { return m_FSM; }
	CHARACTER_TYPE getMonsterType() { return m_type; }
private:
	float m_startX, m_startY;
	float m_pos;

	bool m_isDie;
	bool isDirection;
};