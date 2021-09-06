#pragma once
#include "Cmonster.h"
#include "CFSMController.h"

class Cmario;
class CmonsterWorld :public Cmonster
{
private:
	animation* m_ani;
	CHARACTER_TYPE m_type;
	CFSMController* m_FSM;
	MONSTER_MOVE_TYPE m_moveType;
	Cmario* m_player;

public:
	CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type);
	CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type, Cmario* player);
	virtual ~CmonsterWorld() = default;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void render(MONSTER_TYPE type);

	virtual void attack();
	virtual void move();

	void moveAi();

	void setGoombaStats();
	void setSkyTroopbStats();
	void setSpikeyStats();

	CFSMController* getMonsterFSM() { return m_FSM; }
	CHARACTER_TYPE getMonsterType() { return m_type; }
private:
	float m_startX, m_startY;
	float m_pos;

	bool isDirection;
};