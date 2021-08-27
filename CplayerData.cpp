#include "framework.h"
#include "CplayerData.h"

CplayerData::CplayerData() 
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
