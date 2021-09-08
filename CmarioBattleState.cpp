#include "framework.h"
#include "CmarioBattleState.h"
#include "CplayerManager.h"

player_Battle_Idle::player_Battle_Idle()
{
	m_eState = STATE_TYPE::IDLE;
}

player_Battle_Idle::~player_Battle_Idle()
{
}

void player_Battle_Idle::update()
{
	if (InputManager->isStayKeyDown(VK_F4))
	{
		m_FSM->changeState(STATE_TYPE::MYTURN);
	}

	if (SEQUENCE->getVecSequence()[0] == m_FSM->getUnit()->getNum())
	{
		m_FSM->changeState(STATE_TYPE::MYTURN);
	}
}

void player_Battle_Idle::Enter()
{
}

void player_Battle_Idle::Exit()
{
}


player_MyTurn::player_MyTurn()
{
	m_eState = STATE_TYPE::MYTURN;
}

player_MyTurn::~player_MyTurn()
{
}

void player_MyTurn::update()
{
	if (InputManager->isOnceKeyDown('A'))
	{
		m_FSM->changeState(STATE_TYPE::ITEM);
	}
	else if (InputManager->isOnceKeyDown('S'))
	{
		m_FSM->changeState(STATE_TYPE::ATTACK);
	}
	else if (InputManager->isOnceKeyDown('X'))
	{
		m_FSM->changeState(STATE_TYPE::ETC);
	}
	else if (InputManager->isOnceKeyDown('Z'))
	{
		m_FSM->changeState(STATE_TYPE::SKILL);
	}
}

void player_MyTurn::Enter()
{
}

void player_MyTurn::Exit()
{
}

player_Attack::player_Attack()
{
	m_eState = STATE_TYPE::ATTACK;
}

player_Attack::~player_Attack()
{
}

void player_Attack::update()
{
	if (InputManager->isOnceKeyDown('A'))
	{
		m_FSM->changeState(STATE_TYPE::ITEM);
	}
	else if (InputManager->isOnceKeyDown('X'))
	{
		m_FSM->changeState(STATE_TYPE::ETC);
	}
	else if (InputManager->isOnceKeyDown('Z'))
	{
		m_FSM->changeState(STATE_TYPE::SKILL);
	}
}

void player_Attack::Enter()
{
}

void player_Attack::Exit()
{
}

player_Item::player_Item()
{
	m_eState = STATE_TYPE::ITEM;
}

player_Item::~player_Item()
{
}

void player_Item::update()
{
	if (InputManager->isOnceKeyDown('A'))
	{
		m_FSM->changeState(STATE_TYPE::ITEM);
	}
	else if (InputManager->isOnceKeyDown('S'))
	{
		m_FSM->changeState(STATE_TYPE::ATTACK);
	}
	else if (InputManager->isOnceKeyDown('X'))
	{
		m_FSM->changeState(STATE_TYPE::ETC);
	}
	else if (InputManager->isOnceKeyDown('Z'))
	{
		m_FSM->changeState(STATE_TYPE::SKILL);
	}
}

void player_Item::Enter()
{
}

void player_Item::Exit()
{
}

player_Skill::player_Skill()
{
	m_eState = STATE_TYPE::SKILL;
}

player_Skill::~player_Skill()
{
}

void player_Skill::update()
{
	if (InputManager->isOnceKeyDown('A'))
	{
		m_FSM->changeState(STATE_TYPE::ITEM);
	}
	else if (InputManager->isOnceKeyDown('S'))
	{
		m_FSM->changeState(STATE_TYPE::ATTACK);
	}
	else if (InputManager->isOnceKeyDown('X'))
	{
		m_FSM->changeState(STATE_TYPE::ETC);
	}
	else if (InputManager->isOnceKeyDown('Z'))
	{
		m_FSM->changeState(STATE_TYPE::SKILL);
	}
}

void player_Skill::Enter()
{
}

void player_Skill::Exit()
{
}


player_ETC::player_ETC()
{
	m_eState = STATE_TYPE::ETC;
}

player_ETC::~player_ETC()
{
}

void player_ETC::update()
{
	if (InputManager->isOnceKeyDown('A'))
	{
		m_FSM->changeState(STATE_TYPE::ITEM);
	}
	else if (InputManager->isOnceKeyDown('S'))
	{
		m_FSM->changeState(STATE_TYPE::ATTACK);
	}
	else if (InputManager->isOnceKeyDown('X'))
	{
		m_FSM->changeState(STATE_TYPE::RUN);
	}
	else if (InputManager->isOnceKeyDown('Z'))
	{
		m_FSM->changeState(STATE_TYPE::SKILL);
	}
}

void player_ETC::Enter()
{
}

void player_ETC::Exit()
{
}

player_Run::player_Run()
{
	m_eState = STATE_TYPE::RUN;
}

player_Run::~player_Run()
{
}

void player_Run::update()
{
	m_FSM->changeState(STATE_TYPE::IDLE);
}

void player_Run::Enter()
{
}

void player_Run::Exit()
{
}

player_Defence::player_Defence()
{
}

player_Defence::~player_Defence()
{
}

void player_Defence::update()
{
}

void player_Defence::Enter()
{
}

void player_Defence::Exit()
{
}

