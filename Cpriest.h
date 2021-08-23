#pragma once
#include "Cenemy.h"
#include "CprogressBar.h"
class Cpriest :public Cenemy
{
private:
	CprogressBar* m_hpBar;

public:
	Cpriest();
	~Cpriest();

	virtual HRESULT init(POINT position, float HP, float damage, float def, int exp, float trace);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void attack();
	virtual void die();
	virtual void animation();
	virtual bool enemyCooltime();

	void fire();
};

