#include "framework.h"
#include "CplayerData.h"

CplayerData::CplayerData()
	:m_atk(10), m_def(10), m_hp(40), m_maxHp(m_hp), m_mp(10), m_maxMp(m_mp), m_lv(1), m_exp(10), m_gold(0),
	m_sceneNum(0b0010), m_beforeSceneNum(0b0010), m_speed(3.0f), m_x(WINSIZEX / 2 + 50), m_y(WINSIZEY / 2 + 600), m_isFight(false)
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

void CplayerData::setData(int atk, int def, int hp, int maxhp, int mp, int maxmp, int lv, int exp, int gold, float speed, float x, float y, int num, int beforeNum, bool isFight)
{
	m_atk = atk;
	m_def = def;
	m_hp = hp;
	m_maxHp = maxhp;
	m_mp = mp;
	m_maxMp = maxmp;
	m_sceneNum = num;
	m_beforeSceneNum = beforeNum;
	m_lv = lv;
	m_exp = exp;
	m_gold = gold;
	m_speed = speed;
	m_x = x;
	m_y = y;
	m_isFight = isFight;
}
