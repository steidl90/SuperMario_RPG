#pragma once
class Cstate;
class Cunit;
class Cmario;
class CmarioBattle;
class CpeachBattle;
class CmonsterWorld;
class CFSM
{
private:
	vector<Cstate*> m_vState;
	Cstate* m_curState;
	Cunit* m_unit;
	Cmario* m_player;
	CmarioBattle* m_playerBattle;
	CpeachBattle* m_peachBattle;
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
	void setPeachBattleMemory(CpeachBattle* peachbattle) { m_peachBattle = peachbattle; }

	Cstate* getState() { return m_curState; }
	Cunit* getUnit() { return m_unit; }
	Cmario* getPlayer() { return m_player; }
	CmarioBattle* getPlayerBattle() { return m_playerBattle; }
	CpeachBattle* getPeachBattle() { return m_peachBattle; }
	CmonsterWorld* getMonster() { return m_monster; }
};