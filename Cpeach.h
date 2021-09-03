#pragma once
#include "Cunit.h"
class Cpeach :public Cunit
{
private:

public:
	Cpeach();
	~Cpeach();

	HRESULT init();
	void release();
	void update();
	void render();

	virtual void move();
	virtual void attack();
};