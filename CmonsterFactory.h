#pragma once
#include "Cmonster.h"
#include "Cmario.h"
#include "CplayerManager.h"
class CmonsterFactory
{
private:
	Cmario* m_player;
	CplayerManager* m_playerBattle;
public:
	CmonsterFactory() = default;
	~CmonsterFactory() = default;

	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats);
	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats, Cmario* player);
	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats, CplayerManager* playerBattle);

	static void deleteMonster(Cmonster* monster);
};