#pragma once
#include "Cunit.h"
class CFSM;
class CFSMController
{
protected:
	CFSM* m_AI;
	vector<CFSM*> vAI;

public:
	CFSMController();
	~CFSMController() = default;

	void initState(Cunit* unit, CHARACTER_TYPE type);
	void updateState();
	STATE_TYPE getstate();
	CFSM* getAI() { return m_AI; }
};

