#pragma once
#include "gameNode.h"
#include "Cbattle.h"
#include "CplayerManager.h"
#include "CmonsterManager.h"
class CsceneBattle :public gameNode
{
private:
	Cbattle* m_battle;
	CplayerManager* m_playerM;
	CmonsterManager* m_monsterM;
public:
	CsceneBattle();
	~CsceneBattle() = default;

	HRESULT init();
	void release();
	void update();
	void render();

	void scenechange();
};