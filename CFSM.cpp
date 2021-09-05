#include "framework.h"
#include "CFSM.h"
#include "Cstate.h"
#include "Cmario.h"

CFSM::CFSM() :m_unit(nullptr), m_curState(nullptr), m_player(nullptr)
{
}
CFSM::CFSM(Cunit* unit) :m_unit(unit), m_curState(nullptr), m_player(nullptr)
{
}

CFSM::~CFSM()
{
}

void CFSM::update()
{
	m_curState->update(); //현재 상태
}

void CFSM::addState(Cstate* state)
{
	//상태 추가
	state->setFSM(this);
	m_vState.push_back(state);
}

void CFSM::changeState(STATE_TYPE type)
{
	m_curState->Exit();
	for (int i = 0; i < m_vState.size(); i++)
	{
		if (type == m_vState[i]->getStateType())
		{
			m_curState = m_vState[i];
			m_curState->Enter();
			return;
		}
	}
}

void CFSM::setState(STATE_TYPE type)
{
	for (int i = 0; i < m_vState.size(); i++)
	{
		if (type == m_vState[i]->getStateType())
		{
			m_curState = m_vState[i];
			m_curState->Enter();
			return;
		}
	}
}
