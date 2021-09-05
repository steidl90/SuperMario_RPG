#include "framework.h"
#include "CmonsterManager.h"
#include "CplayerManager.h"
#include "CFSM.h"
#include "Cmario.h"

CmonsterManager::CmonsterManager() :m_stats({NULL}), m_monster(nullptr), vMonster(), viMonster(vMonster.begin()), m_player(nullptr),
m_FSM(new CFSMController)
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

	//m_FSM = new CFSMController;

	for (viMonster = vMonster.begin(); viMonster < vMonster.end(); ++viMonster)
	{
		(*viMonster)->init();
		//m_FSM->initState((*viMonster), CHARACTER_TYPE::MONSTER_WORLD);
	}

	//m_FSM->getAI()->setPlayerMemory(m_player);

    return S_OK;
}

void CmonsterManager::release()
{
	SAFE_DELETE(m_FSM);
}

void CmonsterManager::update()
{
	/*if (m_FSM->getstate()==STATE_TYPE::MOVE)
	{*/
		for (viMonster = vMonster.begin(); viMonster < vMonster.end(); ++viMonster)
		{
			(*viMonster)->update();
		}
	//}
	//m_FSM->updateState();
}

void CmonsterManager::render()
{
	/*if (m_FSM->getstate() == STATE_TYPE::MOVE || m_FSM->getstate() == STATE_TYPE::IDLE)
	{*/
		for (viMonster = vMonster.begin(); viMonster < vMonster.end(); ++viMonster)
		{
			(*viMonster)->render();
		}
	//}
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
	case CHARACTER_TYPE::MONSTER_WORLD:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::MONSTER_WORLD, x, y, RectMake(x, y, IMAGE->findImage("굼바이동")->getFrameWidth(), IMAGE->findImage("굼바이동")->getFrameHeight()), m_stats, m_player);
		break;
	case CHARACTER_TYPE::SKYTROOPA_WORLD:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SKYTROOPA_WORLD, x, y, RectMake(x, y, IMAGE->findImage("날개거북이이동")->getFrameWidth(), IMAGE->findImage("날개거북이이동")->getFrameHeight()), m_stats, m_player);
		break;
	case CHARACTER_TYPE::SPIKEY_WORLD:
		m_monster = CmonsterFactory::createMonster(CHARACTER_TYPE::SPIKEY_WORLD, x, y, RectMake(x, y, IMAGE->findImage("가시돌이이동")->getFrameWidth(), IMAGE->findImage("가시돌이이동")->getFrameHeight()), m_stats, m_player);
		break;
	}

	vMonster.push_back(m_monster);
}
