#pragma once
#include "Cmonster.h"
class Cskytroopa :public Cmonster
{
private:
	using Cmonster::Cmonster;
	virtual ~Cskytroopa();

	int x, y;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void updata();
	virtual void render();

	virtual void attack();
};