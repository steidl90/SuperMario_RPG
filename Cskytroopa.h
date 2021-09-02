#pragma once
#include "Cmonster.h"
class Cskytroopa :public Cmonster
{
private:
	using Cmonster::Cmonster;

	Cskytroopa();
	virtual ~Cskytroopa() = default;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void updata();
	virtual void render();

	virtual void attack();
	virtual void run();
};