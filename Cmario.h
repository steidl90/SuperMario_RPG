#pragma once
#include "Ccharacter.h"
class Cmario :public Ccharacter
{
private:
	MOVE_TYPE direction;
	animation* m_ani;

	char str[20];

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

	RECT* getRect() { return &m_rc; }

};