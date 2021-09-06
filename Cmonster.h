#pragma once
#include "Cunit.h"
class Cmonster :public Cunit
{
private:
	friend class CmonsterFactory;
	
	using Cunit::Cunit;

public:
	virtual ~Cmonster() = default;

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void render(MONSTER_TYPE type) = 0;

};