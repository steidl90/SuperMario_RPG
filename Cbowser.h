#pragma once
#include "Cunit.h"
class Cbowser :public Cunit
{
private:

public:
	Cbowser();
	~Cbowser();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void run();
	virtual void attack();
};
