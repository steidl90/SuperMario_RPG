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
	CHARACTER_TYPE m_type;
	
private:
	float m_x, m_y;

	int m_num;
public:
	CsceneBattle();
	~CsceneBattle();

	HRESULT init();
	void release();
	void update();
	void render();

	void scenechange();

	void setMonsterType();

	void initSequence();
};