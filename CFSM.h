#pragma once

class Cstate;
class Ccharacter;
class CFSM
{
private:
	vector<Cstate*> m_vState;
	Cstate* m_curState;
	Ccharacter* m_character;
public:
	CFSM(Ccharacter* character);
	~CFSM();

	void update();

	void addState(Cstate* state);
	void changeState(STATE_TYPE type);
	void setState(STATE_TYPE type);

	Cstate* getState() { return m_curState; }
	Ccharacter* getCharacter() { return m_character; }
};