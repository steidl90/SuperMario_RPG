#pragma once
#include "Cunit.h"
#include "Cmevius.h"

//�ʿ����..

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

