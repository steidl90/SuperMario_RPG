#pragma once
#include "Cunit.h"
class Cmario :public Cunit
{
private:

public:
	Cmario();
	Cmario(float x, float y, RECT rc, stats stats);
	~Cmario();

	HRESULT init();
	void release();
	void update();
	void render();
};