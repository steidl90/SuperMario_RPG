#pragma once
#include "Cunit.h"
#include "CmarioBattleUi.h"
#include "CFSMController.h"
class CmarioBattle :public Cunit
{
private:
	MOVE_TYPE direction;
	animation* m_ani;
	CFSMController* m_FSM;
	CmarioBattleUi* m_UI;

	char str[20];

	int m_sceneNum;
	int m_beforeSceneNum;

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
	void attack();

	int getSceneNum() { return m_sceneNum; }
	void setSceneNum(int num) { m_sceneNum = num; }

	int getBeforeSceneNum() { return m_beforeSceneNum; }
	void setBeforeSceneNum(int num) { m_beforeSceneNum = num; }

	CFSMController* getFSM() { return m_FSM; }
};

