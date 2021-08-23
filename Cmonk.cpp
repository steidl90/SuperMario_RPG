#include "framework.h"
#include "Cmonk.h"
#include "CenemyAttack.h"
#include "Cplayer.h"

Cmonk::Cmonk()
{
	m_walkImage = nullptr;
}

Cmonk::~Cmonk()
{
}

HRESULT Cmonk::init(POINT position, float HP, float damage, float def, int exp, float trace)
{
	m_enemyAttack = new CenemyAttack;
	m_enemyAttack->init(5, 100, true , "根农傍拜窍");

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

	ANIMATION->addAnimation("根农窍", "根农", 0, 5, 8,	false,	 true);
	ANIMATION->addAnimation("根农谅", "根农", 6, 11, 8,	false,	 true);
	ANIMATION->addAnimation("根农快", "根农", 12, 17, 8,	 false,	 true);
	ANIMATION->addAnimation("根农惑", "根农", 18, 23, 8,		false,	 true);

	m_walkImage = IMAGE->findImage("根农");
	m_walkAni = ANIMATION->findAnimation("根农窍");
	ANIMATION->start("根农窍");

	isSetAstar = false;


	return S_OK;
}

void Cmonk::release()
{
	SAFE_DELETE(m_enemyAttack);
	//SAFE_DELETE(m_player);
	SAFE_DELETE(m_hpBar);
	EFFECT->release();
}

void Cmonk::update()
{
	/*m_aStar->setTargetIndex(PointMake(m_player->getPlayerX() / TILESIZE, m_player->getPlayerY() / TILESIZE));
	m_aStar->setStartIndex(PointMake(m_x / TILESIZE, m_y / TILESIZE));*/

	//if (isDetect)
	//{
	//	m_aStar->update();
	//}

	//if (m_aStar->getFastLoadLocation() != nullptr)
	//{
	//	if (m_aStar->getFastLoadLocation()->size() > 0)
	//	{
	//		if (isAstarSet) isAstarStart = true;

	//		isAstarSet = false;
	//	}
	//	else
	//		isAstarSet = true;
	//}

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
}

void Cmonk::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkRc.right, m_walkRc.bottom);
		Rectangle(getMapDC(), m_traceRc.left, m_traceRc.top, m_traceRc.right, m_traceRc.bottom);
		Rectangle(getMapDC(), m_dieRc.left, m_dieRc.top, m_dieRc.right, m_dieRc.bottom);
	}
	m_hpBar->mapRender();
	IMAGE->findImage("老馆阁胶磐眉仿官")->render(getMapDC(), m_x -20, m_y - 48);
		if (m_isWalking)m_walkImage->aniRender(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkAni);
		if (m_isDie)m_dieImage->aniRender(getMapDC(), m_dieRc.left, m_dieRc.top, m_dieAni);
	if(!m_isDie)m_enemyAttack->render();
	EFFECT->render();

}

void Cmonk::attack()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerMoveRC(), &m_traceRc))
	{
		if (m_player->getplayerMoveRC()->right >= m_walkRc.left - m_distance && m_state == STATE::LEFT)
		{
			m_isWalking = false;
				m_enemyAttack->init2(1, 1, true, "根农傍拜谅");
				m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
					m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "根农傍拜", "根农傍拜谅");
		}

		else if (m_player->getplayerMoveRC()->left <= m_walkRc.right + m_distance && m_state == STATE::RIGHT)
		{
			m_isWalking = false;
				m_enemyAttack->init2(1, 1, true, "根农傍拜快");
				m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
					m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "根农傍拜", "根农傍拜快");
		}

		if (m_player->getplayerMoveRC()->bottom >= m_walkRc.top - m_distance && m_state == STATE::UP)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "根农傍拜惑");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "根农傍拜", "根农傍拜惑");
		}

		if (m_player->getplayerMoveRC()->top <= m_walkRc.bottom + m_distance && m_state == STATE::DOWN)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "根农傍拜窍");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2+10, 0, 1.0f, "根农傍拜", "根农傍拜窍");
		}
	}
}

void Cmonk::die()
{

		if (m_state == STATE::LEFT)
		{
			EFFECT->addEffect("根农荤噶谅", "images/DieMotion/LeftMonkDie.bmp", 912, 111, 76, 111, 1, 0.05f, 1);

			EFFECT->play("根农荤噶谅", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
		}
		if (m_state == STATE::RIGHT)
		{
			EFFECT->addEffect("根农荤噶快", "images/DieMotion/RightMonkDie.bmp", 912, 111, 76, 111, 1, 0.05f, 1);

			EFFECT->play("根农荤噶快", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
		}
		if (m_state == STATE::UP)
		{
			EFFECT->addEffect("根农荤噶惑", "images/DieMotion/UpMonkDie.bmp", 912, 111, 76, 111, 1, 0.05f, 1);

			EFFECT->play("根农荤噶惑", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
		}
		if (m_state == STATE::DOWN)
		{
			EFFECT->addEffect("根农荤噶窍", "images/DieMotion/DownMonkDie.bmp", 912, 111, 76, 111, 1, 0.05f, 1);

			EFFECT->play("根农荤噶窍", m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2);
		}
}

void Cmonk::animation()
{
	switch (m_state)
	{
	case STATE::LEFT:
		m_walkImage = IMAGE->findImage("根农");
		m_walkAni = ANIMATION->findAnimation("根农谅");
		ANIMATION->resume("根农谅");
		//m_attackImage = IMAGE->findImage("根农傍拜");
		//m_attackAni = ANIMATION->findAnimation("根农傍拜谅");
		//ANIMATION->start("根农傍拜谅");
		//m_dieImage = IMAGE->findImage("根农荤噶");
		//m_dieAni = ANIMATION->findAnimation("根农荤噶谅");
		//ANIMATION->resume("根农荤噶谅");
		break;
	case STATE::RIGHT:
		m_walkImage = IMAGE->findImage("根农");
		m_walkAni = ANIMATION->findAnimation("根农快");
		ANIMATION->resume("根农快");
		//m_attackImage = IMAGE->findImage("根农傍拜快");
		//m_attackAni = ANIMATION->findAnimation("根农傍拜快");
		//ANIMATION->start("根农傍拜快");
		//m_dieImage = IMAGE->findImage("根农荤噶");
		//m_dieAni = ANIMATION->findAnimation("根农荤噶快");
		//ANIMATION->resume("根农荤噶快");
		break;
	case STATE::UP:
		m_walkImage = IMAGE->findImage("根农");
		m_walkAni = ANIMATION->findAnimation("根农惑");
		ANIMATION->resume("根农惑");
		//m_attackImage = IMAGE->findImage("根农傍拜");
		//m_attackAni = ANIMATION->findAnimation("根农傍拜惑");
		//ANIMATION->start("根农傍拜惑");
		//m_dieImage = IMAGE->findImage("根农荤噶");
		//m_dieAni = ANIMATION->findAnimation("根农荤噶惑");
		//ANIMATION->resume("根农荤噶惑");
		break;
	case STATE::DOWN:
		m_walkImage = IMAGE->findImage("根农");
		m_walkAni = ANIMATION->findAnimation("根农窍");
		ANIMATION->resume("根农窍");
		//m_attackImage = IMAGE->findImage("根农傍拜");
		//m_attackAni = ANIMATION->findAnimation("根农傍拜窍");
		//ANIMATION->start("根农傍拜窍");
		//m_dieImage = IMAGE->findImage("根农荤噶");
		//m_dieAni = ANIMATION->findAnimation("根农荤噶窍");
		//ANIMATION->resume("根农荤噶窍");
		break;
	}
}

bool Cmonk::enemyCooltime()
{
	m_cooltimeCount++;

	if (m_cooltimeCount % m_rndskillCount == 0)
	{
		m_rndskillCount = 100;
		m_cooltimeCount = 0;
		return true;
	}
	return false;
}

void Cmonk::ReturnIdleAnimation()
{
	m_isAttack = false;
}


