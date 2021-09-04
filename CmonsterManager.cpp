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
	case CHARACTER_TYPE::GOOMBA_WORLD:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::GOOMBA_WORLD, x, y, RectMake(x, y, IMAGE->findImage("�����̵�")->getFrameWidth(), IMAGE->findImage("�����̵�")->getFrameHeight()), m_stats);
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SKYTROOPA_WORLD, x, y, RectMake(x, y, IMAGE->findImage("�����ź����̵�")->getFrameWidth(), IMAGE->findImage("�����ź����̵�")->getFrameHeight()), m_stats);
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SPIKEY_WORLD, x, y, RectMake(x, y, IMAGE->findImage("���õ����̵�")->getFrameWidth(), IMAGE->findImage("���õ����̵�")->getFrameHeight()), m_stats);
		break;
	}

	vMonster.push_back(m_monster);
}
