#pragma once
#include "Cmonster.h"
#include "CFSMController.h"
class CmonsterWorld :public Cmonster
{
private:
	animation* m_ani;
	CHARACTER_TYPE m_type;
	CFSMController* m_FSM;
	MONSTER_MOVE_TYPE m_moveType;

	float m_startX, m_startY;
	float m_pos;
public:
	CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type);
	virtual ~CmonsterWorld() = default;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();
	virtual void move();

	void moveAi();

	void setGoombaStats();
	void setSkyTroopbStats();
	void setSpikeyStats();

private:
	bool isDirection;
};