#include "framework.h"
#include "Celemental.h"
#include "CenemyAttack.h"
#include "Cplayer.h"

Celemental::Celemental()
{
}

Celemental::~Celemental()
{
}

HRESULT Celemental::init(POINT position, float HP, float damage, float def, int exp, float trace)
{
	m_enemyAttack = new CenemyAttack;
	m_enemyAttack->init(50, 500, false, "ø§∏Æ∏‡≈ªΩ∫≈≥æ÷¥œ");

	m_aStar = new CaStar;
	m_aStar->init();
	m_aStar->setAttribute(m_attribute);

	m_isWalking = true;
	m_state = STATE::DOWN;
	m_distance = 100;
	m_x = m_returnX = position.x;
	m_y = m_returnY = position.y;
	m_trace = trace;
	m_speed = 2.0f;
	m_hp = m_maxHp = HP;
	m_damage= damage;
	m_def = def;
	m_exp=exp;

	m_hpBar = new CprogressBar;
	m_hpBar->init("images/hp.bmp", "images/hp_back.bmp", m_x, m_y, 33, 4);
	m_hpBar->setGauge(m_hp, m_maxHp);

	m_cooltimeCount = 0;
	m_rndskillCount = 100;

	ANIMATION->addAnimation("ø§∏Æ∏‡≈ª«œ", "ø§∏Æ∏‡≈ª", 0, 3, 8, false, true);
	ANIMATION->addAnimation("ø§∏Æ∏‡≈ª¡¬", "ø§∏Æ∏‡≈ª", 4, 7, 8, false, true);
	ANIMATION->addAnimation("ø§∏Æ∏‡≈ªøÏ", "ø§∏Æ∏‡≈ª", 8, 11, 8, false, true);
	ANIMATION->addAnimation("ø§∏Æ∏‡≈ªªÛ", "ø§∏Æ∏‡≈ª", 12, 15, 8, false, true);
	
	m_walkImage = IMAGE->findImage("ø§∏Æ∏‡≈ª");
	m_walkAni = ANIMATION->findAnimation("ø§∏Æ∏‡≈ª«œ");
	ANIMATION->start("ø§∏Æ∏‡≈ª«œ");

	isSetAstar = true;

	return S_OK;
}

void Celemental::release()
{
	SAFE_DELETE(m_enemyAttack);
	SAFE_DELETE(m_hpBar);
	SAFE_DELETE(m_aStar);
}

void Celemental::update()
{
	if (isDetect)
	{
		m_aStar->setTargetIndex(PointMake(m_player->getPlayerX() / TILESIZE, m_player->getPlayerY() / TILESIZE));
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

	m_walkRc = RectMakeCenter(m_x, m_y, m_walkImage->getFrameWidth(), m_walkImage->getFrameHeight());
	m_traceRc = RectMakeCenter(m_x, m_y, m_trace, m_trace);
}

void Celemental::render()
{
	if (InputManager->isToggleKey(VK_TAB))
	{
		Rectangle(getMapDC(), m_traceRc.left, m_traceRc.top, m_traceRc.right, m_traceRc.bottom);
		Rectangle(getMapDC(), m_walkRc.left, m_walkRc.top, m_walkRc.right, m_walkRc.bottom);
	}
	m_hpBar->mapRender();
	IMAGE->findImage("¿œπ›∏ÛΩ∫≈Õ√º∑¬πŸ")->render(getMapDC(), m_x-21, m_y - 48);
	if (m_isWalking)m_walkImage->aniRender(getMapDC(), m_walkRc.left-4, m_walkRc.top, m_walkAni);
	m_enemyAttack->render();
}

void Celemental::attack()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerMoveRC(), &m_traceRc))
	{
		if (enemyCooltime()) 
		{
				m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top)/2,
				UTIL::getAngle(m_walkRc.left + (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom + (m_walkRc.top - m_walkRc.bottom) / 2,
				m_player->getplayerMoveRC()->left + (m_player->getplayerMoveRC()->right - m_player->getplayerMoveRC()->left) / 2,
				m_player->getplayerMoveRC()->top+(m_player->getplayerMoveRC()->bottom - m_player->getplayerMoveRC()->top) / 2),
				5.0f, "ø§∏Æ∏‡≈ªΩ∫≈≥3", "ø§∏Æ∏‡≈ªΩ∫≈≥æ÷¥œ");
		}
	}
}

void Celemental::animation()
{
	switch (m_state)
	{
	case STATE::LEFT:
		m_walkImage = IMAGE->findImage("ø§∏Æ∏‡≈ª");
		m_walkAni = ANIMATION->findAnimation("ø§∏Æ∏‡≈ª¡¬");
		ANIMATION->resume("ø§∏Æ∏‡≈ª¡¬");
		break;
	case STATE::RIGHT:
		m_walkImage = IMAGE->findImage("ø§∏Æ∏‡≈ª");
		m_walkAni = ANIMATION->findAnimation("ø§∏Æ∏‡≈ªøÏ");
		ANIMATION->resume("ø§∏Æ∏‡≈ªøÏ");
		break;
	case STATE::UP:
		m_walkImage = IMAGE->findImage("ø§∏Æ∏‡≈ª");
		m_walkAni = ANIMATION->findAnimation("ø§∏Æ∏‡≈ªªÛ");
		ANIMATION->resume("ø§∏Æ∏‡≈ªªÛ");
		break;
	case STATE::DOWN:
		m_walkImage = IMAGE->findImage("ø§∏Æ∏‡≈ª");
		m_walkAni = ANIMATION->findAnimation("ø§∏Æ∏‡≈ª«œ");
		ANIMATION->resume("ø§∏Æ∏‡≈ª«œ");
		break;
	}
}

bool Celemental::enemyCooltime()
{
	m_cooltimeCount++;

	if (m_cooltimeCount % m_rndskillCount == 0)
	{
		m_cooltimeCount = 0;
		return true;
	}
	return false;
}





