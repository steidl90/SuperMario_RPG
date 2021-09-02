#pragma once
#include "Cmonster.h"
class CmonsterFactory
{
private:

public:
	CmonsterFactory() = default;
	~CmonsterFactory() = default;

	static Cmonster* createMonster(CHARACTER_TYPE _type, float x, float y, RECT rc, stats stats);
	static void deleteMonster(Cmonster* monster);
};