#pragma once

class Cstate;
class Cunit;
class CFSM
{
private:
	vector<Cstate*> m_vState;
	Cstate* m_curState;
	Cunit* m_unit;
public:
	CFSM(Cunit* unit);
	~CFSM();

	void update();

	void addState(Cstate* state);
	void changeState(STATE_TYPE type);
	void setState(STATE_TYPE type);

	Cstate* getState() { return m_curState; }
	Cunit* getUnit() { return m_unit; }
};