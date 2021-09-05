#pragma once
#include "Cmonster.h"
#include "Cmario.h"
class CmonsterFactory
{
private:
	Cmario* m_player;
public:
	CmonsterFactory() = default;
	~CmonsterFactory() = default;

	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats);
	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats, Cmario* player);
	static void deleteMonster(Cmonster* monster);
};