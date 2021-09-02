#pragma once
#include "gameNode.h"
#include "Ctown.h"
#include "CplayerManager.h"
class CsceneTown : public gameNode
{
private:
	Ctown* m_town;
	CplayerManager* m_playerM;

private:
	RECT m_doorA;
	RECT m_doorB;

public:
	CsceneTown();
	~CsceneTown();

	HRESULT init();
	void release();
	void update();
	void render();

	void scenechange();
};