#include "framework.h"
#include "CFSMController.h"
#include "CFSM.h"
#include "CmarioState.h"
#include "CmarioBattleState.h"
#include "CmonsterWorldState.h"
#include "CgoombaState.h"

CFSMController::CFSMController() :m_AI(nullptr)
{
}

void CFSMController::initState(Cunit* unit, CHARACTER_TYPE type)
{
	m_AI = new CFSM(unit);
	
	switch (type)
	{
	case CHARACTER_TYPE::PLAYER_WORLD:
		m_AI->addState(new player_Idle);
		m_AI->addState(new player_Move);
		m_AI->addState(new player_Battle);
		m_AI->addState(new player_Die);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::PLAYER_BATTLE:
		m_AI->addState(new player_Battle_Idle);
		m_AI->addState(new player_MyTurn);
		m_AI->addState(new player_Attack);
		m_AI->addState(new player_Item);
		m_AI->addState(new player_Skill);
		m_AI->addState(new player_ETC);
		m_AI->addState(new player_Run);
		m_AI->addState(new player_Defence);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::GOOMBA_WORLD:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::GOOMBA_BATTLE:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::SKYTROOPA_BATTLE:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::SPIKEY_BATTLE:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	}
		
}

void CFSMController::initState(CmonsterWorld* monster, CHARACTER_TYPE type)
{
	m_AI = new CFSM(monster);

	switch (type)
	{
	case CHARACTER_TYPE::GOOMBA_WORLD:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::GOOMBA_BATTLE:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::SKYTROOPA_BATTLE:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
		break;
	case CHARACTER_TYPE::SPIKEY_BATTLE:
		m_AI->addState(new monster_Idle);
		m_AI->addState(new monster_Move);
		m_AI->addState(new monster_Die);
		m_AI->addState(new monster_Battle);
		m_AI->addState(new monster_Trace);
		m_AI->addState(new monster_Attack);
		m_AI->setState(STATE_TYPE::IDLE);
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
