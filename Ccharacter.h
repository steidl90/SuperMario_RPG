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
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	void initAI(Ccharacter* character, CHARACTER_TYPE type);
	void updateAI();
	STATE_TYPE getstate();

	CFSM* getAI() { return m_AI; }
};

