#pragma once
#include "Cmonster.h"
class Cspikey :public Cmonster
{
private:
	using Cmonster::Cmonster;
	virtual ~Cspikey();

	int x, y;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void updata();
	virtual void render();

	virtual void attack();
};