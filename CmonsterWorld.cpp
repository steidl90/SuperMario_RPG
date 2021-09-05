#include "framework.h"
#include "CmonsterWorld.h"
#include "CFSM.h"

CmonsterWorld::CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type) :Cmonster(x, y, rc, stats),
m_type(type), m_ani(), m_FSM(new CFSMController), isDirection(true), m_moveType(MONSTER_MOVE_TYPE::RIGHTDOWN),
m_pos(40.0f), m_startX(NULL), m_startY(NULL), m_player(nullptr)
{
}

CmonsterWorld::CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type, Cmario* player) :Cmonster(x, y, rc, stats),
m_type(type), m_ani(), m_FSM(new CFSMController), isDirection(true), m_moveType(MONSTER_MOVE_TYPE::RIGHTDOWN),
m_pos(40.0f), m_startX(NULL), m_startY(NULL), m_player(player)
{
}

HRESULT CmonsterWorld::init()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::MONSTER_WORLD:
		m_ani = ANIMATION->findAnimation("��������");
		ANIMATION->start("��������");
		m_stats.speed = 1.0f;
		setGoombaStats();
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		m_ani = ANIMATION->findAnimation("�����ź�������");
		ANIMATION->start("�����ź�������");
		m_stats.speed = 5.0f;
		setSkyTroopbStats();
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		m_ani = ANIMATION->findAnimation("���õ�������");
		ANIMATION->start("���õ�������");
		m_stats.speed = 3.0f;
		setSpikeyStats();
		break;
	}
	
	m_startX = m_x;
	m_startY = m_y;
	return S_OK;
}

void CmonsterWorld::release()
{
}

void CmonsterWorld::update()
{
	move();
}

void CmonsterWorld::render()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::MONSTER_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("�����̵�"), ZUNIT, 0, m_x, m_y, m_ani);
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("�����ź����̵�"), ZUNIT, 0, m_x, m_y, m_ani);
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("���õ����̵�"), ZUNIT, 0, m_x, m_y, m_ani);
		break;
	}
}

void CmonsterWorld::attack()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::MONSTER_WORLD:
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		break;
	}
}

void CmonsterWorld::move()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::MONSTER_WORLD:
		moveAi();
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		moveAi();
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		moveAi();
		break;
	}
}

void CmonsterWorld::moveAi()
{
	switch (m_moveType)
	{
	case MONSTER_MOVE_TYPE::RIGHTDOWN:
		if (m_startX + m_pos >= m_x)m_x += m_stats.speed;
		else m_startX = m_x;
		if (m_startY + m_pos >= m_y)m_y += m_stats.speed;
		else
		{
			m_startY = m_y;
			if (isDirection) m_moveType = MONSTER_MOVE_TYPE::LEFTDOWN;
			else m_moveType = MONSTER_MOVE_TYPE::RIGHTUP;
		}
		break;
	case MONSTER_MOVE_TYPE::LEFTDOWN:
		if (m_startX - m_pos <= m_x)m_x -= m_stats.speed;
		else m_startX = m_x;
		if (m_startY + m_pos >= m_y)m_y += m_stats.speed;
		else
		{
			m_startY = m_y;
			if (isDirection) m_moveType = MONSTER_MOVE_TYPE::LEFTUP;
			else m_moveType = MONSTER_MOVE_TYPE::RIGHTDOWN;
		}
		break;
	case MONSTER_MOVE_TYPE::LEFTUP:
		if (m_startX - m_pos <= m_x)m_x -= m_stats.speed;
		else m_startX = m_x;
		if (m_startY - m_pos <= m_y)m_y -= m_stats.speed;
		else
		{
			m_startY = m_y;
			if (isDirection)m_moveType = MONSTER_MOVE_TYPE::RIGHTUP;
			else
			{
				isDirection = true;
				m_moveType = MONSTER_MOVE_TYPE::RIGHTDOWN;
			}
		}
		break;
	case MONSTER_MOVE_TYPE::RIGHTUP:
		if (m_startX + m_pos >= m_x)m_x += m_stats.speed;
		else m_startX = m_x;
		if (m_startY - m_pos <= m_y)m_y -= m_stats.speed;
		else
		{
			m_startY = m_y;
			if (isDirection)
			{
				isDirection = false;
				m_moveType = MONSTER_MOVE_TYPE::LEFTDOWN;
			}
			else m_moveType = MONSTER_MOVE_TYPE::LEFTUP;
		}
		break;
	}
}

void CmonsterWorld::setGoombaStats()
{
}

void CmonsterWorld::setSkyTroopbStats()
{
}

void CmonsterWorld::setSpikeyStats()
{
}