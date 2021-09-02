#pragma once
#include "Cmonster.h"
class Cgoomba :public Cmonster
{
private:
	using Cmonster::Cmonster;
	virtual ~Cgoomba();

	int x, y;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void updata();
	virtual void render();

	virtual void attack();

};

