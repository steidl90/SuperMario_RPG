#pragma once

class CFSM;
class Cstate
{
protected:
	CFSM* m_FSM;
	STATE_TYPE m_eState;

public:
	Cstate();
	~Cstate();

	STATE_TYPE getStateType() { return m_eState; }
	void setFSM(CFSM* fsm) { m_FSM = fsm; }

	virtual void update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
};

