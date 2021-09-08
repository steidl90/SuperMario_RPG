#pragma once
class Cstate;
class Cunit;
class Cmario;
class CmarioBattle;
class CmonsterWorld;
class CFSM
{
private:
	vector<Cstate*> m_vState;
	Cstate* m_curState;
	Cunit* m_unit;
	Cmario* m_player;
	CmarioBattle* m_playerBattle;
	CmonsterWorld* m_monster;
public:
	CFSM();
	CFSM(Cunit* unit);
	CFSM(CmonsterWorld* monster);
	~CFSM();

	void update();

	void addState(Cstate* state);
	void changeState(STATE_TYPE type);
	void setState(STATE_TYPE type);
	void setPlayerMemory(Cmario* player) { m_player = player; }
	void setPlayerBattleMemory(CmarioBattle* playerbattle) { m_playerBattle = playerbattle; }

	Cstate* getState() { return m_curState; }
	Cunit* getUnit() { return m_unit; }
	Cmario* getPlayer() { return m_player; }
	CmarioBattle* getPlayerBattle() { return m_playerBattle; }
	CmonsterWorld* getMonster() { return m_monster; }
};