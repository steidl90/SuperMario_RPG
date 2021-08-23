#include "framework.h"
#include "Cpriest.h"
#include "CenemyAttack.h"
#include "Cplayer.h"

Cpriest::Cpriest()
{
}

Cpriest::~Cpriest()
{
}

HRESULT Cpriest::init(POINT position, float HP, float damage, float def, int exp, float trace)
{
	m_enemyAttack = new CenemyAttack;
	m_enemyAttack->init(50, 500, false, "리치스킬애니");

	//m_player = new Cplayer;
	//m_player->init();

	m_isIdle = false;
	m_state = STATE::DOWN;

	m_x = m_returnX = position.x;
	m_y = m_returnY = position.y;
	m_trace = trace;

	m_distance = 100.0f;
	m_speed = 2.0f;
	m_hp = m_maxHp = HP;
	m_damage = damage;
	m_def = def;
	m_exp = exp;

	m_hpBar = new CprogressBar;
	m_hpBar->init("images/hp.bmp", "images/hp_back.bmp", m_x, m_y, 39, 4);
	m_hpBar->setGauge(m_hp, m_maxHp);

	m_cooltimeCount = 130;
	m_rndskillCount = 129;

	m_isWalking = true;
	m_isDie = false;

	ANIMATION->addAnimation("리치하", "리치", 0, 5, 8, false, true);
	ANIMATION->addAnimation("리치좌", "리치", 6, 11, 8, false, true);
	ANIMATION->addAnimation("리치우", "리치", 12, 17, 8, false, true);
	ANIMATION->addAnimation("리치상", "리치", 18, 23, 8, false, true);

	ANIMATION->addAnimation("리치공격하", "리치공격", 0, 15, 8,	true, true);
	ANIMATION->addAnimation("리치공격좌", "리치공격", 16, 31, 8,	true, true);
	ANIMATION->addAnimation("리치공격우", "리치공격", 32, 47, 8,  true, true);
	ANIMATION->addAnimation("리치공격상", "리치공격", 48, 63, 8,  true, true);



	m_walkImage = IMAGE->findImage("리치");
	m_walkAni = ANIMATION->findAnimation("리치하");
	ANIMATION->start("리치하");

	isSetAstar = false;

	return S_OK;
}

void Cpriest::release()
{
	SAFE_DELETE(m_enemyAttack);
	//SAFE_DELETE(m_player);
	SAFE_DELETE(m_hpBar);
	EFFECT->release();
}

void Cpriest::update()
{

	m_hpBar->setGauge(m_hp, m_maxHp);
	m_hpBar->mapUpdate(m_x - 18, m_y - 65);
	m_enemyAttack->update();
	move();
	attack();
	if (m_hp <= 0)
	{
		m_isDie = true;
		if (m_isDie)
		{
			die();
			m_isDie = false;
		}
	}
	m_walkRc = RectMakeCenter(m_x, m_y, m_walkImage->getFrameWidth(), m_walkImage->getFrameHeight());
	m_traceRc = RectMakeCenter(m_x, m_y, m_trace, m_trace);
}

void Cpriest::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkRc.right, m_walkRc.bottom);
		Rectangle(getMapDC(), m_traceRc.left, m_traceRc.top, m_traceRc.right, m_traceRc.bottom);
		Rectangle(getMapDC(), m_dieRc.left, m_dieRc.top, m_dieRc.right, m_dieRc.bottom);
	}
	m_hpBar->mapRender();
	IMAGE->findImage("레어몬스터체력바")->render(getMapDC(), m_x -27, m_y - 71);
	if (m_isWalking)m_walkImage->aniRender(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkAni);
	m_enemyAttack->render();
}

void Cpriest::attack()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerMoveRC(), &m_traceRc))
	{
		m_cooltimeCount++;

		if (m_state == STATE::LEFT)
		{
			m_walkImage = IMAGE->findImage("리치공격");
			m_walkAni = ANIMATION->findAnimation("리치공격좌");
			ANIMATION->fullstart("리치공격좌");
			fire();

		}
		if (m_state == STATE::RIGHT)
		{
			m_walkImage = IMAGE->findImage("리치공격");
			m_walkAni = ANIMATION->findAnimation("리치공격우");
			ANIMATION->fullstart("리치공격우");
			fire();

		}
		if (m_state == STATE::UP)
		{
			m_walkImage = IMAGE->findImage("리치공격");
			m_walkAni = ANIMATION->findAnimation("리치공격상");
			ANIMATION->fullstart("리치공격상");
			fire();
		}
		if (m_state == STATE::DOWN)
		{
			m_walkImage = IMAGE->findImage("리치공격");
			m_walkAni = ANIMATION->findAnimation("리치공격하");
			ANIMATION->fullstart("리치공격하");
			fire();

		}
	}
}

void Cpriest::die()
{
	if (m_state == STATE::LEFT)
	{
	EFFECT->addEffect("리치사망좌", "images/DieMotion/LeftPriestDie.bmp", 490, 141, 49, 141, 1, 0.05f, 1);
		EFFECT->play("리치사망좌", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
			m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
	if (m_state == STATE::RIGHT)
	{
	EFFECT->addEffect("리치사망우", "images/DieMotion/RightPriestDie.bmp", 490, 141, 49, 141, 1, 0.05f, 1);
		EFFECT->play("리치사망우", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
			m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
	if (m_state == STATE::UP)
	{
	EFFECT->addEffect("리치사망상", "images/DieMotion/UpPriestDie.bmp", 490, 141, 49, 141, 1, 0.05f, 1);
		EFFECT->play("리치사망상", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
			m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
	if (m_state == STATE::DOWN)
	{
	EFFECT->addEffect("리치사망하", "images/DieMotion/DownPriestDie.bmp", 490, 141, 49, 141, 1, 0.05f, 1);
		EFFECT->play("리치사망하", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
			m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
}

void Cpriest::animation()
{
	switch (m_state)
	{
	case STATE::LEFT:
		m_walkImage = IMAGE->findImage("리치");
		m_walkAni = ANIMATION->findAnimation("리치좌");
		ANIMATION->resume("리치좌");
		break;
	case STATE::RIGHT:
		m_walkImage = IMAGE->findImage("리치");
		m_walkAni = ANIMATION->findAnimation("리치우");
		ANIMATION->resume("리치우");
		break;
	case STATE::UP:
		m_walkImage = IMAGE->findImage("리치");
		m_walkAni = ANIMATION->findAnimation("리치상");
		ANIMATION->resume("리치상");
		break;
	case STATE::DOWN:
		m_walkImage = IMAGE->findImage("리치");
		m_walkAni = ANIMATION->findAnimation("리치하");
		ANIMATION->resume("리치하");
		break;
	}
}

bool Cpriest::enemyCooltime()
{

	if (m_cooltimeCount % m_rndskillCount == 0)
	{
		m_rndskillCount = 100;
		m_cooltimeCount = 0;
		return true;
	}
	return false;
}

void Cpriest::fire()
{
	if (enemyCooltime()) {
		m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
			m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2,
			UTIL::getAngle(m_walkRc.left + (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom + (m_walkRc.top - m_walkRc.bottom) / 2,
				m_player->getplayerMoveRC()->left + (m_player->getplayerMoveRC()->right - m_player->getplayerMoveRC()->left) / 2,
				m_player->getplayerMoveRC()->top + (m_player->getplayerMoveRC()->bottom - m_player->getplayerMoveRC()->top) / 2),
			5.0f, "리치스킬", "리치스킬애니");
	}
}
