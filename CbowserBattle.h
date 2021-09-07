#pragma once
#include "Cunit.h"
#include "CFSMController.h"
class CbowserBattle :public Cunit
{
private:
	MOVE_TYPE direction;
	animation* m_ani;
	CFSMController* m_FSM;

	char str[20];

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
	void attack();

	CFSMController* getFSM() { return m_FSM; }
};
