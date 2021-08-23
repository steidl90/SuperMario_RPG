#include "framework.h"
#include "Cprison.h"
#include "CenemyAttack.h"
#include "Cplayer.h"

Cprison::Cprison()
{
}

Cprison::~Cprison()
{
}

HRESULT Cprison::init(POINT position, float HP, float damage, float def, int exp, float trace)
{
	m_enemyAttack = new CenemyAttack;
	m_enemyAttack->init(5, 100, true, "교도관공격하");

	m_aStar = new CaStar;
	m_aStar->init();
	m_aStar->setAttribute(m_attribute);

	m_isIdle = false;
	m_state = STATE::DOWN;

	m_x = m_returnX = position.x;
	m_y = m_returnY = position.y;
	m_trace = trace;

	m_distance = 10.0f;
	m_speed = 20.0f;
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

	ANIMATION->addAnimation("교도관하", "교도관", 0, 7, 8, false, true);
	ANIMATION->addAnimation("교도관좌", "교도관", 8, 15, 8, false, true);
	ANIMATION->addAnimation("교도관우", "교도관", 16, 23, 8, false, true);
	ANIMATION->addAnimation("교도관상", "교도관", 24, 31, 8, false, true);

	m_walkImage = IMAGE->findImage("교도관");
	m_walkAni = ANIMATION->findAnimation("교도관하");
	ANIMATION->start("교도관하");

	isSetAstar = true;

	return S_OK;
}

void Cprison::release()
{
	SAFE_DELETE(m_enemyAttack);
	SAFE_DELETE(m_hpBar);
	SAFE_DELETE(m_aStar);
}

void Cprison::update()
{

	if (isDetect)
	{
		m_aStar->setTargetIndex(PointMake((m_player->getPlayerX()) / TILESIZE, (m_player->getPlayerY()) / TILESIZE));
		m_aStar->setStartIndex(PointMake(m_x / TILESIZE, m_y / TILESIZE));
		m_aStar->update();
	}
	else
	{
		m_aStar->setTargetIndex(PointMake(m_returnX / TILESIZE, m_returnY / TILESIZE));
		m_aStar->setStartIndex(PointMake(m_x / TILESIZE, m_y / TILESIZE));
		m_aStar->update();
	}

	if (m_aStar->getFastLoadLocation() != nullptr)
	{
		if (m_aStar->getFastLoadLocation()->size() > 0)
		{
			if (isAstarSet) isAstarStart = true;
			isAstarSet = false;

			setAstarRoot(*m_aStar->getFastLoadLocation());
		}
		else
			isAstarSet = true;
	}

	m_hpBar->setGauge(m_hp, m_maxHp);
	m_hpBar->mapUpdate(m_x - 15, m_y - 45);
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
	m_astarRc = RectMake(m_x, m_y, TILESIZE, TILESIZE);
}

void Cprison::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMapDC(), m_astarRc.left, m_astarRc.top, m_astarRc.right, m_astarRc.bottom);
		//Rectangle(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkRc.right, m_walkRc.bottom);
		Rectangle(getMapDC(), m_traceRc.left, m_traceRc.top, m_traceRc.right, m_traceRc.bottom);
		//Rectangle(getMapDC(), m_dieRc.left, m_dieRc.top, m_dieRc.right, m_dieRc.bottom);
	}
	m_hpBar->mapRender();
	IMAGE->findImage("일반몬스터체력바")->render(getMapDC(), m_x -21, m_y - 48);
	if (m_isWalking)m_walkImage->aniRender(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkAni);
	m_enemyAttack->render();
	//TCHAR str[256];
	//sprintf_s(str, "%.2f,%.2f", x,y);
	//TextOut(getMemDC(),500,500, str, strlen(str));
	//TCHAR a[256];
	//sprintf_s(a, "%.2f,%.2f", m_player->getPlayerX(), m_player->getPlayerY());
	//TextOut(getMemDC(), 500, 550, a, strlen(a));
}

void Cprison::attack()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerMoveRC(), &m_traceRc))
	{
		if (m_player->getplayerMoveRC()->right >= m_walkRc.left - m_distance&& 
			m_player->getplayerMoveRC()->top >=m_walkRc.top-50 &&
			m_player->getplayerMoveRC()->bottom <= m_walkRc.bottom + 50 && m_state == STATE::LEFT)
		{

			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "교도관공격좌");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "교도관공격", "교도관공격좌");
		}

		else if (m_player->getplayerMoveRC()->left < m_walkRc.right + (m_distance*5) &&
			m_player->getplayerMoveRC()->top >= m_walkRc.top - 50 &&
			m_player->getplayerMoveRC()->bottom <= m_walkRc.bottom + 50 && m_state == STATE::RIGHT)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "교도관공격우");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "교도관공격", "교도관공격우");
		}

		else if (m_player->getplayerMoveRC()->bottom >= m_walkRc.top - m_distance &&
			m_player->getplayerMoveRC()->left >= m_walkRc.left - 50 &&
			m_player->getplayerMoveRC()->right <= m_walkRc.right + 50 && m_state == STATE::UP)
		{
			m_enemyAttack->init2(1, 1, true, "교도관공격상");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "교도관공격", "교도관공격상");
			m_isWalking = false;
		}

		else if (m_player->getplayerMoveRC()->top <= m_walkRc.bottom + m_distance &&
			m_player->getplayerMoveRC()->left >= m_walkRc.left - 50 &&
			m_player->getplayerMoveRC()->right <= m_walkRc.right + 50 && m_state == STATE::DOWN)
		{
			m_enemyAttack->init2(1, 1, true, "교도관공격하");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2 + 10, 0, 1.0f, "교도관공격", "교도관공격하");
			m_isWalking = false;
		}
		else m_isWalking = true;
	}
}

void Cprison::die()
{
	if (m_state == STATE::LEFT)
	{
		EFFECT->addEffect("교도관사망좌", "images/DieMotion/LeftPrisonGuardDie.bmp", 1164, 90, 97, 90, 1, 0.05f, 1);
		EFFECT->play("교도관사망좌", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2, m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
	if (m_state == STATE::RIGHT)
	{
		EFFECT->addEffect("교도관사망우", "images/DieMotion/RightPrisonGuardDie.bmp", 1164, 90, 97, 90, 1, 0.05f, 1);
		EFFECT->play("교도관사망우", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
	if (m_state == STATE::UP)
	{
		EFFECT->addEffect("교도관사망상", "images/DieMotion/UpPrisonGuardDie.bmp", 1164, 90, 97, 90, 1, 0.05f, 1);
		EFFECT->play("교도관사망상", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2, m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
	if (m_state == STATE::DOWN) 
	{
		EFFECT->addEffect("교도관사망하", "images/DieMotion/DownPrisonGuardDie.bmp", 1164, 90, 97, 90, 1, 0.05f, 1);
		EFFECT->play("교도관사망하", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
	}
}

void Cprison::animation()
{
	switch (m_state)
	{
	case STATE::LEFT:
		m_walkImage = IMAGE->findImage("교도관");
		m_walkAni = ANIMATION->findAnimation("교도관좌");
		ANIMATION->resume("교도관좌");
		break;
	case STATE::RIGHT:
		m_walkImage = IMAGE->findImage("교도관");
		m_walkAni = ANIMATION->findAnimation("교도관우");
		ANIMATION->resume("교도관우");
		break;
	case STATE::UP:
		m_walkImage = IMAGE->findImage("교도관");
		m_walkAni = ANIMATION->findAnimation("교도관상");
		ANIMATION->resume("교도관상");
		break;
	case STATE::DOWN:
		m_walkImage = IMAGE->findImage("교도관");
		m_walkAni = ANIMATION->findAnimation("교도관하");
		ANIMATION->resume("교도관하");
		break;
	}
}

bool Cprison::enemyCooltime()
{
	return false;
}
