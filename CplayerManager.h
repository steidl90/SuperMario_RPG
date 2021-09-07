#pragma once
#include "Cunit.h"
#include "Cmario.h"
#include "CmarioBattle.h"
#include "CpeachBattle.h"
#include "CbowserBattle.h"
#include "CFSMController.h"
class CplayerManager :public Cunit
{
private:
	Cmario* m_mario;
	CmarioBattle* m_marioBattle;
	CpeachBattle* m_peachBattle;
	CbowserBattle* m_bowserBattle;
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
	CmarioBattle* getMarioBattle() { return m_marioBattle; }

};