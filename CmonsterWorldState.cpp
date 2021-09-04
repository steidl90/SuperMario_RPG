#include "framework.h"
#include "CmonsterWorldState.h"

monster_Idle::monster_Idle() :m_timer(TIME->getWorldTime())
{
	m_eState = STATE_TYPE::IDLE;
}

monster_Idle::~monster_Idle()
{
}

void monster_Idle::update()
{
	if (m_timer + 1 < TIME->getWorldTime())
	{
		m_FSM->changeState(STATE_TYPE::MOVE);
	}
}

void monster_Idle::Enter()
{
	m_timer = TIME->getWorldTime();

}

void monster_Idle::Exit()
{
}

monster_Move::monster_Move() :m_timer(TIME->getWorldTime())
{
	m_eState = STATE_TYPE::MOVE;
}

monster_Move::~monster_Move()
{}

void monster_Move::update()
{
	if (m_timer + 10 < TIME->getWorldTime())
	{
		m_FSM->changeState(STATE_TYPE::IDLE);
	}
}

void monster_Move::Enter()
{
	m_timer = TIME->getWorldTime();
}

void monster_Move::Exit()
{
}

monster_Trace::monster_Trace()
{
}

monster_Trace::~monster_Trace()
{
}

void monster_Trace::update()
{
}

void monster_Trace::Enter()
{
}

void monster_Trace::Exit()
{
}

monster_Battle::monster_Battle()
{
}

monster_Battle::~monster_Battle()
{
}

void monster_Battle::update()
{
}

void monster_Battle::Enter()
{
}

void monster_Battle::Exit()
{
}

monster_Die::monster_Die()
{
}

monster_Die::~monster_Die()
{
}

void monster_Die::update()
{
}

void monster_Die::Enter()
{
}

void monster_Die::Exit()
{
}
