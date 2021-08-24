#include "framework.h"
#include "Ccharacter.h"
#include "CFSM.h"
#include "CmarioState.h"

Ccharacter::Ccharacter()
{
}

Ccharacter::Ccharacter(float x, float y, RECT rc, stats stats)
{
}

Ccharacter::~Ccharacter()
{
	SAFE_DELETE(m_AI);
}

HRESULT Ccharacter::init()
{
    return S_OK;
}

void Ccharacter::initAI(Ccharacter* character, CHARACTER_TYPE type)
{
    m_AI = new CFSM(character);
	switch (type)
	{
	case CHARACTER_TYPE::PLAYER:
		m_AI->addState(new player_Idle);
		m_AI->addState(new player_Trace);
		m_AI->addState(new player_Atk);
		m_AI->addState(new player_Die);
		m_AI->setState(STATE_TYPE::STATE_TYPE_IDLE);
		break;
	case CHARACTER_TYPE::GOOMBA:
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		break;
	case CHARACTER_TYPE::SPIKEY:
		break;
	default:
		break;
	}
}

void Ccharacter::updateAI()
{
	m_AI->update();
}

STATE_TYPE Ccharacter::getstate()
{
	STATE_TYPE ST = m_AI->getState()->getStateType();
    return ST;
}
