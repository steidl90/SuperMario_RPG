#pragma once
#include "Cobject.h"
class Ctown :public Cobject
{
private:

public:
	Ctown();
	~Ctown();

	HRESULT init();
	void release();
	void update();
	void render();
};

