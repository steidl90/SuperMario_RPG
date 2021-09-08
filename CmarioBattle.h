#pragma once
#include "Cunit.h"
#include "CmarioBattleUi.h"
#include "CFSMController.h"
#include "CmarioBattleState.h"
#include "CmonsterWorld.h"

class CmonsterManager;
class CmarioBattle :public Cunit
{
private:
	MOVE_TYPE direction;
	ATTACK_MOTION curMotion;
	animation* m_ani;
	animation* m_die;
	CFSMController* m_FSM;
	CmarioBattleUi* m_UI;
	CmonsterManager* m_monsterM;
	CmonsterWorld* m_monster;

	char str[20];

	bool isAttack;

	int m_sceneNum;
	int m_beforeSceneNum;
	int monsterNum;

	float timer;
public:
	CmarioBattle();
	~CmarioBattle() = default;

	HRESULT init();
	void release();
	void update();
	void render();

	void animation();
	void action();
	void move();
	void monsterSelect();
	void attack();

	int getSceneNum() { return m_sceneNum; }
	void setSceneNum(int num) { m_sceneNum = num; }

	int getBeforeSceneNum() { return m_beforeSceneNum; }
	void setBeforeSceneNum(int num) { m_beforeSceneNum = num; }

	void setMonsterManagerMemory(CmonsterManager* monsterM) { m_monsterM = monsterM; }

	CFSMController* getFSM() { return m_FSM; }
};

