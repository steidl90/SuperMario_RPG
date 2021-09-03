#pragma once
#include "Cmonster.h"
class CmonsterWorld :public Cmonster
{
private:
	animation* m_ani;
	CHARACTER_TYPE m_type;

public:
	CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type);
	virtual ~CmonsterWorld() = default;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();
	virtual void move();
};