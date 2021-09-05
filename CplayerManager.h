#pragma once
#include "Cunit.h"
#include "Cmario.h"
#include "CmarioBattle.h"
#include "Cpeach.h"
#include "Cbowser.h"
#include "CFSMController.h"
class CplayerManager :public Cunit
{
private:
	Cmario* m_mario;
	CmarioBattle* m_marioBattle;
	Cpeach* m_peach;
	Cbowser* m_bowser;
	CFSMController* m_FSM;

public:
	CplayerManager();
	~CplayerManager() = default;

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void attack();
	virtual void move();

	void isMyTurn();

	RECT* getMarioRect() { return m_mario->getRect(); }
	Cmario* getMario() { return m_mario; }
};