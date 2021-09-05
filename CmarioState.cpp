#include "framework.h"
#include "CmarioState.h"
#include "CplayerManager.h"

player_Idle::player_Idle() :temp(RectMake(0, 0, 0, 0))
{
	m_eState = STATE_TYPE::IDLE;
}

player_Idle::~player_Idle(){}

void player_Idle::update()
{
	if (InputManager->isStayKeyDown(VK_LEFT) ||
		InputManager->isStayKeyDown(VK_RIGHT) ||
		InputManager->isStayKeyDown(VK_UP) ||
		InputManager->isStayKeyDown(VK_DOWN))
	{
		m_FSM->changeState(STATE_TYPE::MOVE);
	}
	
	if (m_FSM->getUnit()->getisFight())
	{
		m_FSM->changeState(STATE_TYPE::BATTLE);
	}
}

void player_Idle::Enter() //초기화
{}
void player_Idle::Exit() //릴리즈
{}

player_Move::player_Move()
{
	m_eState = STATE_TYPE::MOVE;
}

player_Move::~player_Move()
{
}

void player_Move::update()
{
	if (!(InputManager->isStayKeyDown(VK_LEFT) ||
		InputManager->isStayKeyDown(VK_RIGHT) ||
		InputManager->isStayKeyDown(VK_UP) ||
		InputManager->isStayKeyDown(VK_DOWN)))
	{
		m_FSM->changeState(STATE_TYPE::IDLE);
	}

	if (m_FSM->getUnit()->getisFight())
	{
		m_FSM->changeState(STATE_TYPE::BATTLE);
	}
}

void player_Move::Enter()
{
}

void player_Move::Exit()
{
}


player_Battle::player_Battle()
{
	m_eState = STATE_TYPE::BATTLE;
}

player_Battle::~player_Battle()
{
}

void player_Battle::update()
{

}

void player_Battle::Enter()
{
}

void player_Battle::Exit()
{
}

player_Die::player_Die()
{
}

player_Die::~player_Die()
{
}

void player_Die::update()
{
}

void player_Die::Enter()
{
}

void player_Die::Exit()
{
}
