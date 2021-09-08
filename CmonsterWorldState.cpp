#include "framework.h"
#include "CmonsterWorldState.h"
#include "CmonsterFactory.h"

monster_Idle::monster_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

monster_Idle::~monster_Idle()
{}

void monster_Idle::update()
{
	if (m_FSM->getMonster()->getMonsterType() == CHARACTER_TYPE::GOOMBA_WORLD || 
		m_FSM->getMonster()->getMonsterType() == CHARACTER_TYPE::SKYTROOPA_WORLD || 
		m_FSM->getMonster()->getMonsterType() == CHARACTER_TYPE::SPIKEY_WORLD)
	{
		if (m_timer + 1 < TIME->getWorldTime())
		{
			m_FSM->changeState(STATE_TYPE::MOVE);
		}
		if (IntersectRect(&temp, &m_FSM->getMonster()->getRect(), m_FSM->getPlayer()->getRect()))
		{
			m_FSM->getPlayer()->setisFight(true);
			m_FSM->changeState(STATE_TYPE::BATTLE);
		}
	}
	else
	{
		if (SEQUENCE->getVecSequence()[0] == m_FSM->getMonster()->getNum())
		{
			m_FSM->changeState(STATE_TYPE::ATTACK);
		}
	}

	if (m_FSM->getMonster()->getHp() <= 0)
	{
		m_FSM->changeState(STATE_TYPE::DEAD);
	}

}

void monster_Idle::Enter()
{
	m_timer = TIME->getWorldTime();
}

void monster_Idle::Exit()
{
}

//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================

monster_Move::monster_Move()
{
	m_eState = STATE_TYPE::MOVE;
}

monster_Move::~monster_Move()
{}

void monster_Move::update()
{
	if (m_timer + 2.5 < TIME->getWorldTime())
	{
		m_FSM->changeState(STATE_TYPE::IDLE);
	}

	if (IntersectRect(&temp, &m_FSM->getMonster()->getRect(), m_FSM->getPlayer()->getRect()))
	{
		m_FSM->getPlayer()->setisFight(true);
		m_FSM->changeState(STATE_TYPE::BATTLE);
	}
}

void monster_Move::Enter()
{
	m_timer = TIME->getWorldTime();
}

void monster_Move::Exit()
{
}

//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================

monster_Trace::monster_Trace()
{
	m_eState = STATE_TYPE::TRACE;
}

monster_Trace::~monster_Trace()
{}

void monster_Trace::update()
{
	if (IntersectRect(&temp, &m_FSM->getMonster()->getRect(), m_FSM->getPlayer()->getRect()))
	{
		m_FSM->changeState(STATE_TYPE::BATTLE);
	}
}

void monster_Trace::Enter()
{
	m_timer = TIME->getWorldTime();
}

void monster_Trace::Exit()
{
}

//======================================================================================
//======================================================================================
//======================================================================================
//======================================================================================

monster_Battle::monster_Battle()
{
	m_eState = STATE_TYPE::BATTLE;
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
	m_eState = STATE_TYPE::DEAD;
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

monster_Attack::monster_Attack()
{
	m_eState = STATE_TYPE::ATTACK;
}

monster_Attack::~monster_Attack()
{
}

void monster_Attack::update()
{

	switch (curMotion)
	{
	case ATTACK_MOTION::READY:
		break;
	case ATTACK_MOTION::MOVE:
	{
		if (m_FSM->getPlayerBattle()->getX() + 90 <= m_FSM->getMonster()->getX())
			m_FSM->getMonster()->setX(m_FSM->getMonster()->getX() - 20.0f);
		else
		{
			m_timer = TIME->getWorldTime();
			curMotion = ATTACK_MOTION::ATTACK;
		}
		if (m_FSM->getPlayerBattle()->getY() - 85 >= m_FSM->getMonster()->getY())
			m_FSM->getMonster()->setY(m_FSM->getMonster()->getY() + 8.0f);
		else if (m_FSM->getPlayerBattle()->getY() - 85 > m_FSM->getMonster()->getY())
			m_FSM->getMonster()->setY(m_FSM->getMonster()->getY() - 1.0f);
		break;
	}
	case ATTACK_MOTION::ATTACK:
		if (m_FSM->getMonster()->getMonsterType() == CHARACTER_TYPE::GOOMBA_BATTLE) ANIMATION->resume("굼바기본공격");
		else if (m_FSM->getMonster()->getMonsterType() == CHARACTER_TYPE::SKYTROOPA_BATTLE) ANIMATION->resume("날개거북이기본공격");
		else if (m_FSM->getMonster()->getMonsterType() == CHARACTER_TYPE::SPIKEY_BATTLE) ANIMATION->resume("가시돌이기본공격");

		if (m_timer + 1.7f <= TIME->getWorldTime())
			curMotion = ATTACK_MOTION::RETURN;
		break;
	case ATTACK_MOTION::RETURN:
		m_FSM->getMonster()->setX(m_x);
		m_FSM->getMonster()->setY(m_y);
		curMotion = ATTACK_MOTION::READY;
		m_FSM->changeState(STATE_TYPE::IDLE);
		m_FSM->getPlayerBattle()->setHp(m_FSM->getPlayerBattle()->getHp() - 1);
		SEQUENCE->remover();
		break;
	}
}

void monster_Attack::Enter()
{
	curMotion = ATTACK_MOTION::MOVE;
	m_timer = TIME->getWorldTime();
	m_x = m_FSM->getMonster()->getX();
	m_y = m_FSM->getMonster()->getY();
}

void monster_Attack::Exit()
{
	m_timer = TIME->getWorldTime();
}
