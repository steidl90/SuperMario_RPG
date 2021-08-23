#pragma once
#include "Cunit.h"
#include "Cmevius.h"

//필요없음..

class CbossManager :public Cunit
{
private:
	Cmevius* m_mevius;


public:
	CbossManager();
	~CbossManager();

	HRESULT init();
	void release();
	void update();
	void render();


};

