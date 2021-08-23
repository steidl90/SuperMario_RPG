#include "framework.h"
#include "Cslime.h"
#include "CenemyAttack.h"
#include "Cplayer.h"

Cslime::Cslime()
{
}

Cslime::~Cslime()
{
}

HRESULT Cslime::init(POINT position, float HP, float damage, float def, int exp, float trace)
{
	m_enemyAttack = new CenemyAttack;
	m_enemyAttack->init(5, 100, true, "슬라임공격하");

	//m_player = new Cplayer;
	//m_player->init();

	//m_aStar = new CaStar;
	//m_aStar->init();
	//m_aStar->setAttribute(m_attribute);

	m_isIdle = false;
	m_state = STATE::DOWN;

	m_x = m_returnX = position.x;
	m_y = m_returnY = position.y;
	m_trace = trace;

	m_distance = 10.0f;
	m_speed = 2.0f;
	m_hp = m_maxHp = HP;
	m_damage = damage;
	m_def = def;
	m_exp = exp;

	m_hpBar = new CprogressBar;
	m_hpBar->init("images/hp.bmp", "images/hp_back.bmp", m_x, m_y, 33, 4);
	m_hpBar->setGauge(m_hp, m_maxHp);

	m_cooltimeCount = 200;
	m_rndskillCount = 1;

	m_isWalking = true;
	m_isDie = false;

	ANIMATION->addAnimation("슬라임애니", "슬라임", 0, 5, 8, false, true);


	m_walkImage = IMAGE->findImage("슬라임");
	m_walkAni = ANIMATION->findAnimation("슬라임애니");
	ANIMATION->start("슬라임애니");

	isSetAstar = false;

	return S_OK;
}

void Cslime::release()
{
	SAFE_DELETE(m_enemyAttack);
	//SAFE_DELETE(m_player);
	SAFE_DELETE(m_hpBar);
}

void Cslime::update()
{
	/*m_aStar->setTargetIndex(PointMake(m_player->getPlayerX() / TILESIZE, m_player->getPlayerY() / TILESIZE));
	m_aStar->setStartIndex(PointMake(m_x / TILESIZE, m_y / TILESIZE));

	if (isDetect)
	{
		m_aStar->update();
	}

	if (m_aStar->getFastLoadLocation() != nullptr)
	{
		if (m_aStar->getFastLoadLocation()->size() > 0)
		{
			if (isAstarSet) isAstarStart = true;

			isAstarSet = false;
		}
		else
			isAstarSet = true;
	}*/

	m_hpBar->setGauge(m_hp, m_maxHp);
	m_hpBar->mapUpdate(m_x - 15, m_y - 25);
	m_enemyAttack->update();
	move();
	attack();
	if (m_walkImage != nullptr)
	{
		m_walkRc = RectMakeCenter(m_x, m_y, m_walkImage->getFrameWidth(), m_walkImage->getFrameHeight());
	}
	m_traceRc = RectMakeCenter(m_x, m_y, m_trace, m_trace);
}

void Cslime::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkRc.right, m_walkRc.bottom);
		Rectangle(getMapDC(), m_traceRc.left, m_traceRc.top, m_traceRc.right, m_traceRc.bottom);
		Rectangle(getMapDC(), m_dieRc.left, m_dieRc.top, m_dieRc.right, m_dieRc.bottom);
	}
	//IMAGE->findImage("선택그림자")->render(getMapDC(), m_x, m_y);
	m_hpBar->mapRender();
	IMAGE->findImage("일반몬스터체력바")->render(getMapDC(), m_x - 21, m_y - 28);
	if (m_isWalking)m_walkImage->aniRender(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkAni);
	m_enemyAttack->render();
}

void Cslime::attack()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerMoveRC(), &m_traceRc))
	{
		if (m_player->getplayerMoveRC()->right >= m_walkRc.left - m_distance && m_state == STATE::LEFT)
		{

			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "슬라임공격좌");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "슬라임공격", "슬라임공격좌");
		}

		else if (m_player->getplayerMoveRC()->left <= m_walkRc.right + m_distance && m_state == STATE::RIGHT)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "슬라임공격우");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "슬라임공격", "슬라임공격우");
		}

		if (m_player->getplayerMoveRC()->bottom >= m_walkRc.top - m_distance && m_state == STATE::UP)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "슬라임공격상");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "슬라임공격", "슬라임공격상");
		}

		if (m_player->getplayerMoveRC()->top <= m_walkRc.bottom + m_distance && m_state == STATE::DOWN)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "슬라임공격하");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2 + 10, 0, 1.0f, "슬라임공격", "슬라임공격하");
		}
	}
}

void Cslime::animation()
{
	switch (m_state)
	{
	case STATE::LEFT:
		m_walkImage = IMAGE->findImage("슬라임");
		m_walkAni = ANIMATION->findAnimation("슬라임애니");
		ANIMATION->resume("슬라임애니");
		break;
	case STATE::RIGHT:
		m_walkImage = IMAGE->findImage("슬라임");
		m_walkAni = ANIMATION->findAnimation("슬라임애니");
		ANIMATION->resume("슬라임애니");
		break;
	case STATE::UP:
		m_walkImage = IMAGE->findImage("슬라임");
		m_walkAni = ANIMATION->findAnimation("슬라임애니");
		ANIMATION->resume("슬라임애니");
		break;
	case STATE::DOWN:
		m_walkImage = IMAGE->findImage("슬라임");
		m_walkAni = ANIMATION->findAnimation("슬라임애니");
		ANIMATION->resume("슬라임애니");
		break;
	}
}

bool Cslime::enemyCooltime()
{
	return false;
}
