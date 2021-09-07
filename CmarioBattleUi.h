#pragma once
#include "gameNode.h"
class CmarioBattleUi :public gameNode
{
private:

public:
	CmarioBattleUi();
	~CmarioBattleUi();

	HRESULT init();
	void release();
	void update();
	void render();
};

