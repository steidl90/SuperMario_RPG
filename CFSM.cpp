#include "framework.h"
#include "CFSM.h"
#include "Cstate.h"

CFSM::CFSM()
{
}

CFSM::CFSM(Cunit* unit) :m_unit(unit), m_curState()
{
}

CFSM::~CFSM()
{
}

void CFSM::update()
{
	m_curState->update(); //���� ����
}

void CFSM::addState(Cstate* state)
{
	//���� �߰�
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
