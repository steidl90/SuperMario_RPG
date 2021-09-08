#include "framework.h"
#include "CmonsterManager.h"
#include "CplayerManager.h"
#include "CmonsterWorld.h"
#include "Cmario.h"

CmonsterManager::CmonsterManager() :m_stats({ NULL }), m_monster(nullptr), vMonster(), viMonster(vMonster.begin()), m_player(nullptr),
m_CollisionType(CHARACTER_TYPE::GOOMBA_WORLD), timer(TIME->getWorldTime()), m_playerBattle(nullptr)
{
	//memset(&m_stats, 0, sizeof(m_stats));
}

CmonsterManager::~CmonsterManager()
{
}

HRESULT CmonsterManager::init()
{
	isDie = false;
	timer = TIME->getWorldTime();
	for (viMonster = vMonster.begin(); viMonster != vMonster.end(); ++viMonster)
	{
		(*viMonster)->init();
	}

	return S_OK;
}

HRESULT CmonsterManager::init(Cmario* player)
{
	m_stats.lv = 1;
    m_stats.atk = 10;
    m_stats.def = 10;
    m_stats.exp = 10;
	m_stats.maxHp = m_stats.hp = 30;
	m_stats.maxMp = m_stats.mp = 10;
	m_stats.gold = 10;
	
	for (viMonster = vMonster.begin(); viMonster != vMonster.end(); ++viMonster)
	{
		(*viMonster)->init();
	}

    return S_OK;
}

void CmonsterManager::release()
{
}

void CmonsterManager::update()
{
	for (viMonster = vMonster.begin(); viMonster != vMonster.end();)
	{
		(*viMonster)->update();
		if (dynamic_cast<CmonsterWorld*>(*viMonster)->getMonsterFSM()->getstate() == STATE_TYPE::BATTLE)
			m_CollisionType = dynamic_cast<CmonsterWorld*>(*viMonster)->getMonsterType();

		if (dynamic_cast<CmonsterWorld*>(*viMonster)->getMonsterFSM()->getstate() == STATE_TYPE::DEAD)
		{
			m_x = (*viMonster)->getX();
			m_y = (*viMonster)->getY();
			timer = TIME->getWorldTime();
			isDie = true;
			SEQUENCE->remover((*viMonster)->getNum());
			vMonster.erase(viMonster);
			return;
		}
		else ++viMonster;
	}
}

void CmonsterManager::render()
{
	for (viMonster = vMonster.begin(); viMonster != vMonster.end(); ++viMonster)
	{
		(*viMonster)->render();
	}
	if (isDie)
	{
		ANIMATION->resume("사망");
		ZORDER->zorderAniRender(IMAGE->findImage("사망이펙트"), ZUNIT, 0, m_x - 40, m_y - 40, ANIMATION->findAnimation("사망"));
		if (timer + 0.7f <= TIME->getWorldTime())
		{
			isDie = false;
			ANIMATION->initAni("사망");
		}
	}
}

void CmonsterManager::attack()
{
}

void CmonsterManager::move()
{
}

void CmonsterManager::addMonster(CHARACTER_TYPE monster, float x, float y)
{
	switch (monster)
	{
	case CHARACTER_TYPE::GOOMBA_WORLD:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight()), m_stats, m_player);
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight()), m_stats, m_player);
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight()), m_stats, m_player);
		break;
	case CHARACTER_TYPE::GOOMBA_BATTLE:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight()), m_stats, m_playerBattle);
		break;
	case CHARACTER_TYPE::SKYTROOPA_BATTLE:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight()), m_stats, m_playerBattle);
		break;
	case CHARACTER_TYPE::SPIKEY_BATTLE:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight()), m_stats, m_playerBattle);
		break;
	}
	vMonster.push_back(m_monster);
}
