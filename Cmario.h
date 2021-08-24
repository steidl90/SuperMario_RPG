#pragma once
#include "Ccharacter.h"
class Cmario :public Ccharacter
{
private:
	MOVE_TYPE direction;

public:
	Cmario();
	Cmario(float x, float y, RECT rc, stats stats);
	~Cmario();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animation();
};