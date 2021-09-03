#include "framework.h"
#include "CmonsterManager.h"

CmonsterManager::CmonsterManager() :m_stats(), m_monster(), vMonster(), viMonster()
{
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

	for (viMonster = vMonster.begin(); viMonster < vMonster.end(); ++viMonster)
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
	for (viMonster = vMonster.begin(); viMonster < vMonster.end(); ++viMonster)
	{
		(*viMonster)->update();
	}
}

void CmonsterManager::render()
{
	for (viMonster = vMonster.begin(); viMonster < vMonster.end(); ++viMonster)
	{
		(*viMonster)->render();
	}
}

void CmonsterManager::addMonster(CHARACTER_TYPE monster, float x, float y)
{
	switch (monster)
	{
	case CHARACTER_TYPE::GOOMBA:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::GOOMBA, x, y, RectMake(x, y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight()), m_stats);
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SKYTROOPA, x, y, RectMake(x, y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight()), m_stats);
		break;
	case CHARACTER_TYPE::SPIKEY:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SPIKEY, x, y, RectMake(x, y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight()), m_stats);
		break;
	}

	vMonster.push_back(m_monster);
}
