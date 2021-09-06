#include "framework.h"
#include "CmonsterFactory.h"
#include "CmonsterWorld.h"

Cmonster* CmonsterFactory::createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats)
{
	return new CmonsterWorld(x, y, rc, stats, _type);
}

Cmonster* CmonsterFactory::createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats, Cmario* player)
{
	return new CmonsterWorld(x, y, rc, stats, _type, player);
}

void CmonsterFactory::deleteMonster(Cmonster* monster)
{
	delete monster;
}