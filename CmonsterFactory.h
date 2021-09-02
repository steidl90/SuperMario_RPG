#pragma once
#include "Cmonster.h"
#include "Cgoomba.h"
#include "Cskytroopa.h"
class CmonsterFactory
{
public:
	static Cmonster* createMonster(CHARACTER_TYPE _type,int x)
	{
		switch (_type)
		{
		case CHARACTER_TYPE::PLAYER:
			break;
		case CHARACTER_TYPE::GOOMBA:
			return new Cgoomba(x);
			break;
		case CHARACTER_TYPE::SKYTROOPA:
			return new Cskytroopa(x);
			break;
		case CHARACTER_TYPE::SPIKEY:
			break;
		default:
			break;
		}
	}

	static void deleteMonster(Cmonster* monster)
	{
		delete monster;
	}
};

