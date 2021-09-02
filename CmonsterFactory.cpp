#include "framework.h"
#include "CmonsterFactory.h"
#include "Cgoomba.h"
#include "Cskytroopa.h"
#include "Cspikey.h"

Cmonster* CmonsterFactory::createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats)
{
	switch (_type)
	{
	case CHARACTER_TYPE::GOOMBA:
		return new Cgoomba(x, y, rc, stats);
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		return new Cskytroopa(x, y, rc, stats);
		break;
	case CHARACTER_TYPE::SPIKEY:
		return new Cspikey(x, y, rc, stats);
		break;
	}
}

void CmonsterFactory::deleteMonster(Cmonster* monster)
{
	delete monster;
}
