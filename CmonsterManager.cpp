#include "framework.h"
#include "CmonsterManager.h"

CmonsterManager::CmonsterManager() :m_stats(), m_monster(), vGoomBaMonster(), viMonster()
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

	for (viMonster = vGoomBaMonster.begin(); viMonster < vGoomBaMonster.end(); ++viMonster)
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
	for (viMonster = vGoomBaMonster.begin(); viMonster < vGoomBaMonster.end(); ++viMonster)
	{
		(*viMonster)->updata();
	}
}

void CmonsterManager::render()
{
	for (viMonster = vGoomBaMonster.begin(); viMonster < vGoomBaMonster.end(); ++viMonster)
	{
		(*viMonster)->render();
	}
}

void CmonsterManager::addMonster(CHARACTER_TYPE monster)
{
	switch (monster)
	{
	case CHARACTER_TYPE::GOOMBA:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::GOOMBA, 100, 100, RectMake(100, 100, 100, 100), m_stats);
		vGoomBaMonster.push_back(m_monster);
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		break;
	case CHARACTER_TYPE::SPIKEY:
		break;
	default:
		break;
	}

}
