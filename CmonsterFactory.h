#pragma once
#include "Cmonster.h"
#include "Cmario.h"
#include "CmarioBattle.h"
class CmonsterFactory
{
private:
	Cmario* m_player;
	CmarioBattle* m_playerBattle;
public:
	CmonsterFactory() = default;
	~CmonsterFactory() = default;

	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats);
	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats, Cmario* player);
	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats, CmarioBattle* playerBattle);

	static void deleteMonster(Cmonster* monster);
};