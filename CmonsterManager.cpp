#include "framework.h"
#include "CmonsterManager.h"
#include "CplayerManager.h"
#include "CmonsterWorld.h"
#include "CFSM.h"
#include "Cmario.h"

CmonsterManager::CmonsterManager() :m_stats({ NULL }), m_monster(nullptr), vMonster(), viMonster(vMonster.begin()), m_player(nullptr),
m_CollisionType(CHARACTER_TYPE::GOOMBA_WORLD)
{
	//memset(&m_stats, 0, sizeof(m_stats));
}

CmonsterManager::~CmonsterManager()
{
}

HRESULT CmonsterManager::init()
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
	for (viMonster = vMonster.begin(); viMonster != vMonster.end(); ++viMonster)
	{
		(*viMonster)->update();
		if (dynamic_cast<CmonsterWorld*>(*viMonster)->getMonsterFSM()->getstate() == STATE_TYPE::BATTLE)
			m_CollisionType = dynamic_cast<CmonsterWorld*>(*viMonster)->getMonsterType();
	}
}

void CmonsterManager::render()
{
	for (viMonster = vMonster.begin(); viMonster != vMonster.end(); ++viMonster)
	{
		(*viMonster)->render();
		/*(*viMonster)->render(MONSTER_TYPE::WORLD);
		(*viMonster)->render(MONSTER_TYPE::BATTLE);*/
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
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight()), m_stats, m_player);
		break;
	case CHARACTER_TYPE::SKYTROOPA_BATTLE:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight()), m_stats, m_player);
		break;
	case CHARACTER_TYPE::SPIKEY_BATTLE:
		m_monster = CmonsterFactory::createMonster(monster, x, y, RectMake(x, y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight()), m_stats, m_player);
		break;
	}
	vMonster.push_back(m_monster);
}
