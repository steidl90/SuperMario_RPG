#pragma once
class Cstate;
class Cunit;
class Cmario;
class CFSM
{
private:
	vector<Cstate*> m_vState;
	Cstate* m_curState;
	Cunit* m_unit;
	Cmario* m_player;
public:
	CFSM();
	CFSM(Cunit* unit);
	~CFSM();

	void update();

	void addState(Cstate* state);
	void changeState(STATE_TYPE type);
	void setState(STATE_TYPE type);
	void setPlayerMemory(Cmario* player) { m_player = player; }

	Cstate* getState() { return m_curState; }
	Cunit* getUnit() { return m_unit; }
	Cmario* getPlayer() { return m_player; }
};