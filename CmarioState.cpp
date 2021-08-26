#include "framework.h"
#include "CmarioState.h"

player_Idle::player_Idle() //처음 상태
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
	if ((InputManager->isStayKeyDown(VK_LEFT) ||
		InputManager->isStayKeyDown(VK_RIGHT) ||
		InputManager->isStayKeyDown(VK_UP) ||
		InputManager->isStayKeyDown(VK_DOWN)))
	{
		m_FSM->changeState(STATE_TYPE::IDLE);
	}
}

void player_Move::Enter()
{
}

void player_Move::Exit()
{
}
//
//player_Atk::player_Atk()
//{
//	m_eState = STATE_TYPE::ATTACK;
//}
//
//player_Atk::~player_Atk()
//{
//}
//
//void player_Atk::update()
//{
//}
//
//void player_Atk::Enter()
//{
//}
//
//void player_Atk::Exit()
//{
//}
//
//player_Die::player_Die()
//{
//	m_eState = STATE_TYPE::DEAD;
//}
//
//player_Die::~player_Die()
//{
//}
//
//void player_Die::update()
//{
//}
//
//void player_Die::Enter()
//{
//}
//
//void player_Die::Exit()
//{
//}
