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

	for (viMonster = vSkyTroopaMonster.begin(); viMonster < vSkyTroopaMonster.end(); ++viMonster)
	{
		(*viMonster)->init();
	}

	for (viMonster = vSpikeyMonster.begin(); viMonster < vSpikeyMonster.end(); ++viMonster)
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

	for (viMonster = vSkyTroopaMonster.begin(); viMonster < vSkyTroopaMonster.end(); ++viMonster)
	{
		(*viMonster)->updata();
	}

	for (viMonster = vSpikeyMonster.begin(); viMonster < vSpikeyMonster.end(); ++viMonster)
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

	for (viMonster = vSkyTroopaMonster.begin(); viMonster < vSkyTroopaMonster.end(); ++viMonster)
	{
		(*viMonster)->render();
	}

	for (viMonster = vSpikeyMonster.begin(); viMonster < vSpikeyMonster.end(); ++viMonster)
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
		vGoomBaMonster.push_back(m_monster);
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SKYTROOPA, x, y, RectMake(x, y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight()), m_stats);
		vSkyTroopaMonster.push_back(m_monster);
		break;
	case CHARACTER_TYPE::SPIKEY:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SPIKEY, x, y, RectMake(x, y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight()), m_stats);
		vSpikeyMonster.push_back(m_monster);
		break;
	default:
		break;
	}

}
