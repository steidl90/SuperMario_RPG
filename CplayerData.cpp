#include "framework.h"
#include "CplayerData.h"
#include "Citem.h"

CplayerData::CplayerData() 
	:m_hp(1000),m_maxHp(m_hp), m_mp(500), m_maxMp(m_mp), m_exp(0), m_atk(10),
	m_def(10), m_critical(5), m_criticalAtk(1.5), m_speed(3.0), m_lv(1),
	m_gold(1000),m_x(50),m_y(WINSIZEY / 2 + 230),
	m_quest(0),m_maxQuest(50),m_isDialog(false),m_isQuesting(false),m_isComplete(false)
{
}

CplayerData::~CplayerData()
{
}

HRESULT CplayerData::init()
{
	return S_OK;
}

void CplayerData::release()
{
}

void CplayerData::update()
{
}

void CplayerData::render()
{
}

void CplayerData::setData(int atk, int def, int hp, int maxhp, int mp, int maxmp, int cri, int lv, int exp, int gold, float criatk, float speed, float x, float y)
{
	m_atk = atk;
	m_def = def;
	m_hp = hp;
	m_maxHp = maxhp;
	m_mp = mp;
	m_maxMp = maxmp;
	m_critical = cri;
	m_lv = lv;
	m_exp = exp;
	m_gold = gold;
	m_criticalAtk = criatk;
	m_speed = speed;
	m_x = x;
	m_y = y;
}

void CplayerData::setEquipItem(EquipItem* equipItem)
{
	m_equipItem[0] = equipItem[0];
	m_equipItem[1] = equipItem[1];
	m_equipItem[2] = equipItem[2];
	m_equipItem[3] = equipItem[3];
	m_equipItem[4] = equipItem[4];
}

