#pragma once
#include "Cobject.h"
class Cbattle :public Cobject
{
private:

public:
	Cbattle();
	~Cbattle();

	HRESULT init();
	void release();
	void update();
	void render();
};
