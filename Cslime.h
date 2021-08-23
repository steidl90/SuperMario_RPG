#pragma once
#include "Cenemy.h"
#include "CprogressBar.h"
class Cslime :public Cenemy
{
private:
	CprogressBar* m_hpBar;

public:
	Cslime();
	~Cslime();

	virtual HRESULT init(POINT position, float HP, float damage, float def, int exp, float trace);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();
	virtual void animation();
	virtual bool enemyCooltime();
};

