#include "framework.h"
#include "CgoombaState.h"

goomba_Idle::goomba_Idle() :m_timer(TIME->getWorldTime())
{
	m_eState = STATE_TYPE::IDLE;
}

goomba_Idle::~goomba_Idle()
{
}

void goomba_Idle::update()
{
	if (m_timer + 2 > TIME->getWorldTime())
	{
		m_FSM->changeState(STATE_TYPE::MOVE);
	}
}

void goomba_Idle::Enter()
{
	m_timer = TIME->getWorldTime();
}

void goomba_Idle::Exit()
{}

goomba_Move::goomba_Move() :m_timer(TIME->getWorldTime())
{
	m_eState = STATE_TYPE::MOVE;
}

goomba_Move::~goomba_Move()
{
}

void goomba_Move::update()
{
	if (m_timer + 10 < TIME->getWorldTime())
	{
		m_FSM->changeState(STATE_TYPE::IDLE);
	}
}

void goomba_Move::Enter()
{
	m_timer = TIME->getWorldTime();
}

void goomba_Move::Exit()
{
}
