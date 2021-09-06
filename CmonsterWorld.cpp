#include "framework.h"
#include "CmonsterWorld.h"
#include "CFSM.h"
#include "Cmario.h"

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
		m_ani = ANIMATION->findAnimation("굼바좌하");
		ANIMATION->start("굼바좌하");
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight());
		m_stats.speed = 0.75f;
		setGoombaStats();
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		m_ani = ANIMATION->findAnimation("날개거북이좌하");
		ANIMATION->start("날개거북이좌하");
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight());
		m_stats.speed = 1.5f;
		setSkyTroopbStats();
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		m_ani = ANIMATION->findAnimation("가시돌이좌하");
		ANIMATION->start("가시돌이좌하");
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight());
		m_stats.speed = 1.25f;
		setSpikeyStats();
		break;
	}
	/*m_FSM = new CFSMController;
	m_FSM->initState(this, CHARACTER_TYPE::MONSTER_WORLD);
	m_FSM->getAI()->setPlayerMemory(m_player);*/

	m_startX = m_x;
	m_startY = m_y;
	return S_OK;
}

void CmonsterWorld::release()
{
	SAFE_DELETE(m_FSM);
}

void CmonsterWorld::update()
{
	/*if (m_FSM->getstate() == STATE_TYPE::MOVE)*/move();
	//m_FSM->updateState();
}

void CmonsterWorld::render()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::MONSTER_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("굼바이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("날개거북이이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("가시돌이이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		break;
	}

	Rectangle(getMemDC(), getRect().left, getRect().top, getRect().right, getRect().bottom);
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
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight());
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		moveAi();
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight());
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		moveAi();
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight());
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
