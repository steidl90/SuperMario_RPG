#include "framework.h"
#include "CmarioState.h"

player_Idle::player_Idle()
{
	m_eState = STATE_TYPE::STATE_TYPE_IDLE;
}

player_Idle::~player_Idle(){}

void player_Idle::update(){}

void player_Idle::Enter(){}

void player_Idle::Exit(){}

player_Trace::player_Trace()
{
	m_eState = STATE_TYPE::STATE_TYPE_TRACE;
}

player_Trace::~player_Trace()
{
}

void player_Trace::update()
{
}

void player_Trace::Enter()
{
}

void player_Trace::Exit()
{
}

player_Atk::player_Atk()
{
	m_eState = STATE_TYPE::STATE_TYPE_ATTACK;
}

player_Atk::~player_Atk()
{
}

void player_Atk::update()
{
}

void player_Atk::Enter()
{
}

void player_Atk::Exit()
{
}

player_Die::player_Die()
{
	m_eState = STATE_TYPE::STATE_TYPE_DEAD;
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
