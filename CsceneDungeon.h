#pragma once
#include "gameNode.h"
#include "Cdungeon.h"
#include "CplayerManager.h"
#include "CenemyManager.h"
#include "camera.h"
#include "Cmevius.h"
#include "Cquest.h"

class CsceneDungeon : public gameNode
{
private:
	Cdungeon* m_dungeon;
	camera* m_camera;
	CplayerManager* m_player;
	CenemyManager* m_enemyManager;
	Cmevius* m_boss;
	Cquest* m_quest;

	RECT m_changeRect;

public:
	CsceneDungeon();
	~CsceneDungeon();

	HRESULT init();
	void release();
	void update();
	void render();

	void sceneChange();
};
