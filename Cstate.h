#pragma once
#include "CFSM.h"

class CFSM;
class Cstate
{
protected:
	CFSM* m_FSM;
	STATE_TYPE m_eState;
	ATTACK_MOTION curMotion;

	int m_timer;

public:
	Cstate();
	virtual ~Cstate();

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	
	STATE_TYPE getStateType() { return m_eState; }
	ATTACK_MOTION getMotion() { return curMotion; }

	void setFSM(CFSM* fsm) { m_FSM = fsm; }
};

