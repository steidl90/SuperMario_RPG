#pragma once
#include "Cmonster.h"
class Cspikey :public Cmonster
{
private:
	using Cmonster::Cmonster;
	virtual ~Cspikey() = default;

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