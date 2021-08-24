#pragma once
#include "gameNode.h"
#include "Cfacade.h"
#include "Cmario.h"
class mainGame : public gameNode
{
private:
	Cfacade* m_facade;
	Cmario* m_player;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
