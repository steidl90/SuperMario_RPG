#include "framework.h"
#include "CmonsterWorld.h"
#include "CmonsterWorldState.h"
#include "CFSMController.h"
#include "Cmario.h"
#include "CmarioBattle.h"
#include "Cunit.h"

CmonsterWorld::CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type) :Cmonster(x, y, rc, stats),
m_type(type), m_ani(), m_FSM(new CFSMController), isDirection(true), m_moveType(MONSTER_MOVE_TYPE::RIGHTDOWN),
m_pos(40.0f), m_startX(NULL), m_startY(NULL), m_player(nullptr), m_isDie(false)
{
}

CmonsterWorld::CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type, Cmario* player) :Cmonster(x, y, rc, stats),
m_type(type), m_ani(), m_FSM(new CFSMController), isDirection(true), m_moveType(MONSTER_MOVE_TYPE::RIGHTDOWN),
m_pos(40.0f), m_startX(NULL), m_startY(NULL), m_player(player), m_isDie(false)
{
}

CmonsterWorld::CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type, CmarioBattle* m_playerBattle) :Cmonster(x, y, rc, stats),
m_type(type), m_ani(), m_FSM(new CFSMController), isDirection(true), m_moveType(MONSTER_MOVE_TYPE::RIGHTDOWN),
m_pos(40.0f), m_startX(NULL), m_startY(NULL), m_playerBattle(m_playerBattle), m_isDie(false)
{
}

HRESULT CmonsterWorld::init()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::GOOMBA_WORLD:
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
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
	case CHARACTER_TYPE::GOOMBA_BATTLE:
		m_ani = ANIMATION->findAnimation("굼바좌하");
		ANIMATION->start("굼바좌하");
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight());
		setGoombaStats();
		break;
	case CHARACTER_TYPE::SKYTROOPA_BATTLE:
		m_ani = ANIMATION->findAnimation("날개거북이좌하");
		ANIMATION->start("날개거북이좌하");
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight());
		setSkyTroopbStats();
		break;
	case CHARACTER_TYPE::SPIKEY_BATTLE:
		m_ani = ANIMATION->findAnimation("가시돌이좌하");
		ANIMATION->start("가시돌이좌하");
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight());
		setSpikeyStats();
		break;
	}
	m_FSM = new CFSMController;
	m_FSM->initState(this, CHARACTER_TYPE::GOOMBA_WORLD);
	m_FSM->getAI()->setPlayerMemory(m_player);
	m_FSM->getAI()->setPlayerBattleMemory(m_playerBattle);

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
	if (m_FSM->getstate() == STATE_TYPE::MOVE)
		move();

	//if (m_FSM->getstate() == STATE_TYPE::BATTLE)
		attack();

	m_FSM->updateState();
}

void CmonsterWorld::render()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::GOOMBA_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("굼바이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("날개거북이이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		ZORDER->zorderAniRender(IMAGE->findImage("가시돌이이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		break;
	case CHARACTER_TYPE::GOOMBA_BATTLE:
		if (m_FSM->getAI()->getState()->getMotion() == ATTACK_MOTION::ATTACK)
		{
			m_ani = ANIMATION->findAnimation("굼바기본공격");
			ZORDER->zorderAniRender(IMAGE->findImage("굼바공격"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		}
		else 
		{
			m_ani = ANIMATION->findAnimation("굼바좌하");
			ZORDER->zorderAniRender(IMAGE->findImage("굼바이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		}
		break;
	case CHARACTER_TYPE::SKYTROOPA_BATTLE:
		if (m_FSM->getAI()->getState()->getMotion() == ATTACK_MOTION::ATTACK)
		{
			m_ani = ANIMATION->findAnimation("날개거북이기본공격");
			ZORDER->zorderAniRender(IMAGE->findImage("날개거북이공격"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		}
		else
		{
			m_ani = ANIMATION->findAnimation("날개거북이좌하");
			ZORDER->zorderAniRender(IMAGE->findImage("날개거북이이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		}
		break;
	case CHARACTER_TYPE::SPIKEY_BATTLE:
		if (m_FSM->getAI()->getState()->getMotion() == ATTACK_MOTION::ATTACK)
		{
			m_ani = ANIMATION->findAnimation("가시돌이기본공격");
			ZORDER->zorderAniRender(IMAGE->findImage("가시돌이공격"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		}
		else
		{
			m_ani = ANIMATION->findAnimation("가시돌이좌하");
			ZORDER->zorderAniRender(IMAGE->findImage("가시돌이이동"), ZUNIT, 0, m_rc.left, m_rc.top, m_ani);
		}
		break;
	}

	//테스트용
	if (InputManager->isToggleKey(VK_TAB))
	{
		ZORDER->zorderRectangle(m_rc, ZCOLMAP);
	}
}

void CmonsterWorld::attack()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::GOOMBA_BATTLE:
		m_moveType = MONSTER_MOVE_TYPE::LEFTDOWN;
		attackAi();
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight());
		break;
	case CHARACTER_TYPE::SKYTROOPA_BATTLE:
		m_moveType = MONSTER_MOVE_TYPE::LEFTDOWN;
		attackAi();
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight());
		break;
	case CHARACTER_TYPE::SPIKEY_BATTLE:
		m_moveType = MONSTER_MOVE_TYPE::LEFTDOWN;
		attackAi();
		m_rc = RectMake(m_x, m_y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight());
		break;
	}
}

void CmonsterWorld::move()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::GOOMBA_WORLD:
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

void CmonsterWorld::attackAi()
{
	switch (m_moveType)
	{
	case MONSTER_MOVE_TYPE::LEFTDOWN:
		break;
	}
}

void CmonsterWorld::setGoombaStats()
{
	m_stats.lv = 1;
	m_stats.atk = 10;
	m_stats.def = 10;
	m_stats.exp = 10;
	m_stats.maxHp = m_stats.hp = 30;
	m_stats.maxMp = m_stats.mp = 10;
	m_stats.gold = 10;
	m_stats.num = RND->getFromIntTo(4, 1000000);
	m_isDie = false;
}

void CmonsterWorld::setSkyTroopbStats()
{
	m_stats.lv = 1;
	m_stats.atk = 10;
	m_stats.def = 10;
	m_stats.exp = 10;
	m_stats.maxHp = m_stats.hp = 30;
	m_stats.maxMp = m_stats.mp = 10;
	m_stats.gold = 10;
	m_stats.num = RND->getFromIntTo(4, 1000000);
	m_isDie = false;
}

void CmonsterWorld::setSpikeyStats()
{
	m_stats.lv = 1;
	m_stats.atk = 10;
	m_stats.def = 10;
	m_stats.exp = 10;
	m_stats.maxHp = m_stats.hp = 30;
	m_stats.maxMp = m_stats.mp = 10;
	m_stats.gold = 10;
	m_stats.num = RND->getFromIntTo(4, 1000000);
	m_isDie = false;
}
