#pragma once
#include "Cobject.h"
class CbanditsWay :public Cobject
{
private:


public:
	CbanditsWay();
	~CbanditsWay();

	HRESULT init();
	void release();
	void update();
	void render();
};

