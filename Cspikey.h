#pragma once
#include "Cmonster.h"
class Cspikey :public Cmonster
{
private:
	using Cmonster::Cmonster;
	virtual ~Cspikey();

public:

	virtual HRESULT init();
	virtual void release();
	virtual void updata();
	virtual void render();

	virtual void attack();
	virtual void run();
};