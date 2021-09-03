#pragma once
#include "Cmonster.h"
class Cskytroopa :public Cmonster
{
private:
	using Cmonster::Cmonster;
	virtual ~Cskytroopa() = default;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();
	virtual void move();

private:
	animation* m_ani;
};