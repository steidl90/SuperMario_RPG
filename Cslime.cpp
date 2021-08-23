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
	m_enemyAttack->init(5, 100, true, "�����Ӱ�����");

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

	ANIMATION->addAnimation("�����Ӿִ�", "������", 0, 5, 8, false, true);


	m_walkImage = IMAGE->findImage("������");
	m_walkAni = ANIMATION->findAnimation("�����Ӿִ�");
	ANIMATION->start("�����Ӿִ�");

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
	//IMAGE->findImage("���ñ׸���")->render(getMapDC(), m_x, m_y);
	m_hpBar->mapRender();
	IMAGE->findImage("�Ϲݸ���ü�¹�")->render(getMapDC(), m_x - 21, m_y - 28);
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
			m_enemyAttack->init2(1, 1, true, "�����Ӱ�����");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "�����Ӱ���", "�����Ӱ�����");
		}

		else if (m_player->getplayerMoveRC()->left <= m_walkRc.right + m_distance && m_state == STATE::RIGHT)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "�����Ӱ��ݿ�");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "�����Ӱ���", "�����Ӱ��ݿ�");
		}

		if (m_player->getplayerMoveRC()->bottom >= m_walkRc.top - m_distance && m_state == STATE::UP)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "�����Ӱ��ݻ�");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2, 0, 1.0f, "�����Ӱ���", "�����Ӱ��ݻ�");
		}

		if (m_player->getplayerMoveRC()->top <= m_walkRc.bottom + m_distance && m_state == STATE::DOWN)
		{
			m_isWalking = false;
			m_enemyAttack->init2(1, 1, true, "�����Ӱ�����");
			m_enemyAttack->fire(m_walkRc.right - (m_walkRc.right - m_walkRc.left) / 2,
				m_walkRc.bottom - (m_walkRc.bottom - m_walkRc.top) / 2 + 10, 0, 1.0f, "�����Ӱ���", "�����Ӱ�����");
		}
	}
}

void Cslime::animation()
{
	switch (m_state)
	{
	case STATE::LEFT:
		m_walkImage = IMAGE->findImage("������");
		m_walkAni = ANIMATION->findAnimation("�����Ӿִ�");
		ANIMATION->resume("�����Ӿִ�");
		break;
	case STATE::RIGHT:
		m_walkImage = IMAGE->findImage("������");
		m_walkAni = ANIMATION->findAnimation("�����Ӿִ�");
		ANIMATION->resume("�����Ӿִ�");
		break;
	case STATE::UP:
		m_walkImage = IMAGE->findImage("������");
		m_walkAni = ANIMATION->findAnimation("�����Ӿִ�");
		ANIMATION->resume("�����Ӿִ�");
		break;
	case STATE::DOWN:
		m_walkImage = IMAGE->findImage("������");
		m_walkAni = ANIMATION->findAnimation("�����Ӿִ�");
		ANIMATION->resume("�����Ӿִ�");
		break;
	}
}

bool Cslime::enemyCooltime()
{
	return false;
}
