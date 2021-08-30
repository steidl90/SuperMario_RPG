#pragma once
#include "Cobject.h"
class Chouse :public Cobject
{
private:

public:
	Chouse();
	~Chouse();

	HRESULT init();
	void release();
	void update();
	void render();
};
