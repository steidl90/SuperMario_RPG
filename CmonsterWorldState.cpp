#include "framework.h"
#include "CmonsterWorldState.h"
#include "CmonsterManager.h"
#include "CmonsterFactory.h"

monster_Idle::monster_Idle() :m_timer(TIME->getWorldTime()), temp(RectMake(0, 0, 0, 0))
{
	m_eState = STATE_TYPE::IDLE;
}

monster_Idle::~monster_Idle()
{}

void monster_Idle::update()
{
	if (m_timer + 1 < TIME->getWorldTime())
	{
		m_FSM->changeState(STATE_TYPE::MOVE);
	}
	if (IntersectRect(&temp, &m_FSM->getUnit()->getRect(), m_FSM->getPlayer()->getRect()))
	{
		m_FSM->getPlayer()->setisFight(true);
		m_FSM->changeState(STATE_TYPE::BATTLE);
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

monster_Move::monster_Move() :m_timer(TIME->getWorldTime()), temp(RectMake(0, 0, 0, 0))
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

	if (IntersectRect(&temp, &m_FSM->getUnit()->getRect(), m_FSM->getPlayer()->getRect()))
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

monster_Trace::monster_Trace() :m_timer(TIME->getWorldTime()), temp(RectMake(0, 0, 0, 0))
{
	m_eState = STATE_TYPE::TRACE;
}

monster_Trace::~monster_Trace()
{}

void monster_Trace::update()
{
	if (IntersectRect(&temp, &m_FSM->getUnit()->getRect(), m_FSM->getPlayer()->getRect()))
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

monster_Battle::monster_Battle() :m_timer(TIME->getWorldTime())
{
	m_eState = STATE_TYPE::BATTLE;
}

monster_Battle::~monster_Battle()
{
}

void monster_Battle::update()
{
	m_FSM->changeState(STATE_TYPE::IDLE);
	//PLAYERDATA->setData(m_FSM->getPlayer()->getAtk(),
	//	m_FSM->getPlayer()->getDef(),
	//	m_FSM->getPlayer()->getHp(),
	//	m_FSM->getPlayer()->getMaxHp(),
	//	m_FSM->getPlayer()->getMp(),
	//	m_FSM->getPlayer()->getMaxMp(),
	//	m_FSM->getPlayer()->getLv(),
	//	m_FSM->getPlayer()->getExp(),
	//	m_FSM->getPlayer()->getGold(),
	//	m_FSM->getPlayer()->getSpeed(),
	//	m_FSM->getPlayer()->getX(),
	//	m_FSM->getPlayer()->getY(),
	//	m_FSM->getPlayer()->getSceneNum(),
	//	m_FSM->getPlayer()->getBeforeSceneNum(),
	//	m_FSM->getPlayer()->getisFight());
	////m_monsterM->vecClear();
	//SCENE->changeBattleScene("¹èÆ²¸Ê");
}

void monster_Battle::Enter()
{
}

void monster_Battle::Exit()
{
}

monster_Die::monster_Die() :m_timer(TIME->getWorldTime())
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
