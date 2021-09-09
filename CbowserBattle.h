#pragma once
#include "Cunit.h"
#include "CFSMController.h"
#include "CbowserBattleUi.h"

class CmonsterManager;
class CbowserBattle :public Cunit
{
private:
	MOVE_TYPE direction;
	ATTACK_MOTION curMotion;
	animation* m_ani;
	animation* m_die;
	CFSMController* m_FSM;
	CbowserBattleUi* m_UI;
	CmonsterManager* m_monsterM;
	CmonsterWorld* m_monster;

	char str[20];

	bool isAttack;

	int monsterNum;

	float timer;
public:
	CbowserBattle();
	~CbowserBattle() = default;

	HRESULT init();
	void release();
	void update();
	void render();

	void animation();
	void action();
	void move();
	void monsterSelect();
	void attack();

	void setMonsterManagerMemory(CmonsterManager* monsterM) { m_monsterM = monsterM; }

	CFSMController* getFSM() { return m_FSM; }
};
