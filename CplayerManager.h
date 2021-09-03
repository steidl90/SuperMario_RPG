#pragma once
#include "Cunit.h"
#include "Cmario.h"
#include "Cpeach.h"
#include "Cbowser.h"
#include "Ccommand.h"
#include "Cinvoker.h"
class CplayerManager :public Cunit
{
private:
	Cmario* m_mario;
	Cpeach* m_peach;
	Cbowser* m_bowser;

	Cinvoker* m_button;
	Ccommand* m_command;
public:
	CplayerManager();
	~CplayerManager();

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