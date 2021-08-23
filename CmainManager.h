#pragma once
#include "gameNode.h"
#include "CenemyManager.h"
#include "CbossManager.h"
#include "CplayerManager.h"
class CmainManager :public gameNode
{
private:


public:
	CmainManager();
	~CmainManager();

	HRESULT init();
	void release();
	void update();
	void render();
};

