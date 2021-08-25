#pragma once
#include "Cunit.h"
#include "Cmario.h"
#include "Cpeach.h"
#include "Cbowser.h"
class CplayerManager :public Cunit
{
private:
	Cmario* m_mario;
	Cpeach* m_peach;
	Cbowser* m_bowser;

public:
	CplayerManager();
	~CplayerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	RECT* getMarioRect() { return m_mario->getRect(); }
	Cmario* getMario() { return m_mario; }

};