#pragma once
#include "CmonsterFactory.h"
class CmonsterManager
{
private:
	stats m_stats;

	Cmonster* m_monster;

	vector<Cmonster*> vMonster;
	vector<Cmonster*>::iterator viMonster;

public:
	CmonsterManager();
	~CmonsterManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addMonster(CHARACTER_TYPE monster, float x, float y);
};

