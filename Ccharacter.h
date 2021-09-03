#pragma once
#include "Cunit.h"
class CFSM;
class Ccharacter :public Cunit
{
protected:
	CFSM* m_AI;
	vector<CFSM*> vAI;
public:
	Ccharacter();
	Ccharacter(float x, float y, RECT rc, stats stats);
	
	~Ccharacter();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void initAI(Ccharacter* character, CHARACTER_TYPE type);
	void updateAI();
	STATE_TYPE getstate();

	CFSM* getAI() { return m_AI; }
};

