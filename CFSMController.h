#pragma once
#include "Cunit.h"
#include "CmonsterWorld.h"

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
	void initState(CmonsterWorld* monster, CHARACTER_TYPE type);

	void updateState();
	STATE_TYPE getstate();
	CFSM* getAI() { return m_AI; }
};