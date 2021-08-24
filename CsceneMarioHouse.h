#pragma once
#include "gameNode.h"
#include "CplayerManager.h"
class CsceneMarioHouse :public gameNode
{
private:
	CplayerManager* CplayerM;

public:
	CsceneMarioHouse();
	~CsceneMarioHouse();

	HRESULT init();
	void release();
	void update();
	void render();
};

