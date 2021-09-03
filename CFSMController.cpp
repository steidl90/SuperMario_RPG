#include "framework.h"
#include "CFSMController.h"
#include "CFSM.h"
#include "CmarioState.h"
#include "CgoombaState.h"

CFSMController::CFSMController() :m_AI(nullptr)
{
}

void CFSMController::initState(Cunit* unit, CHARACTER_TYPE type)
{
	m_AI = new CFSM(unit);

	switch (type)
	{
	case CHARACTER_TYPE::PLAYER:
		m_AI->addState(new player_Idle);
		m_AI->addState(new player_Move);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::GOOMBA:
		m_AI->addState(new goomba_Idle);
		m_AI->addState(new goomba_Move);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		break;
	case CHARACTER_TYPE::SPIKEY:
		break;
	default:
		break;
	}
}

void CFSMController::updateState()
{
	m_AI->update();
}

STATE_TYPE CFSMController::getstate()
{
	STATE_TYPE ST = m_AI->getState()->getStateType();
	return ST;
}
