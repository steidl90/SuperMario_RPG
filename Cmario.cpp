#include "framework.h"
#include "Cmario.h"
#include "Cstate.h"
#include "CFSM.h"
#include "CmarioState.h"

Cmario::Cmario() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하")), str("마리오하"), prevX(0.0f), prevY(0.0f), m_sceneNum(0), isfight(false)
{
}

Cmario::Cmario(float x, float y, RECT rc, stats stats) :
	Ccharacter(x, y, rc, stats), direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하")), str("마리오하")
{
	m_x = x;
	m_y = y;
	m_rc = rc;
	m_stats.atk = stats.atk;
	m_stats.def = stats.def;
	m_stats.exp = stats.exp;
	m_stats.gold = stats.gold;
	m_stats.hp = stats.hp;
	m_stats.maxHp = stats.maxHp;
	m_stats.lv = stats.lv;
	m_stats.mp = stats.mp;
	m_stats.maxMp = stats.maxMp;
	m_stats.speed = stats.speed;
}

Cmario::~Cmario()
{
}

HRESULT Cmario::init()
{
	m_x = WINSIZEX / 2 + 50;
	m_y = WINSIZEY / 2 + 400;
	m_stats.lv = 1;
	m_stats.atk = 10;
	m_stats.def = 10;
	m_stats.maxHp = m_stats.hp = 30;
	m_stats.maxMp = m_stats.mp = 10;
	m_stats.exp = 10;
	m_stats.gold = 0;
	m_stats.speed = 3.0f;

	prevX = m_x;
	prevY = m_y;

	m_sceneNum = 0b0000;

	setLv(m_stats.lv);
	setAtk(m_stats.atk);
	setDef(m_stats.def);
	setHp(m_stats.hp);
	setMaxHp(m_stats.maxHp);
	setMp(m_stats.mp);
	setMaxMp(m_stats.maxMp);
	setExp(m_stats.exp);
	setGold(m_stats.gold);
	setSpeed(m_stats.speed);
	setX(m_x);
	setY(m_y);

	initAI(this, CHARACTER_TYPE::PLAYER);
	return S_OK;
}

void Cmario::release()
{
}

void Cmario::update()
{
	if (getstate() == STATE_TYPE::IDLE || getstate() == STATE_TYPE::MOVE)
	{
		move();
		animation();
	}
	m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("마리오이동")->getFrameWidth() - 20, IMAGE->findImage("마리오이동")->getFrameHeight() - 20);

	updateAI();
}

void Cmario::render()
{
	if (InputManager->isToggleKey(VK_TAB))Rectangle(getMapDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	ZORDER->zorderAniRender(IMAGE->findImage("마리오이동"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
}

void Cmario::move()
{
	if (InputManager->isStayKeyDown(VK_RIGHT) && InputManager->isStayKeyDown(VK_DOWN))
	{
		setX(getX() + getSpeed() * 0.75);
		setY(getY() + getSpeed() * 0.37);
		direction = MOVE_TYPE::RIGHTDOWN;
	}
	else if (InputManager->isStayKeyDown(VK_RIGHT) && InputManager->isStayKeyDown(VK_UP))
	{
		setX(getX() + getSpeed() * 0.75);
		setY(getY() - getSpeed() * 0.37);
		direction = MOVE_TYPE::RIGHTUP;
	}
	else if (InputManager->isStayKeyDown(VK_LEFT) && InputManager->isStayKeyDown(VK_DOWN))
	{
		setX(getX() - getSpeed() * 0.75);
		setY(getY() + getSpeed() * 0.37);
		direction = MOVE_TYPE::LEFTDOWN;
	}
	else if (InputManager->isStayKeyDown(VK_LEFT) && InputManager->isStayKeyDown(VK_UP))
	{
		setX(getX() - getSpeed() * 0.75);
		setY(getY() - getSpeed() * 0.37);
		direction = MOVE_TYPE::LEFTUP;
	}
	else if (InputManager->isStayKeyDown(VK_LEFT))
	{
		setX(getX() - getSpeed());
		direction = MOVE_TYPE::LEFT;
	}
	else if (InputManager->isStayKeyDown(VK_RIGHT))
	{
		setX(getX() + getSpeed());
		direction = MOVE_TYPE::RIGHT;
	}
	else if (InputManager->isStayKeyDown(VK_UP))
	{
		setY(getY() - getSpeed());
		direction = MOVE_TYPE::UP;
	}
	else if (InputManager->isStayKeyDown(VK_DOWN))
	{
		setY(getY() + getSpeed());
		direction = MOVE_TYPE::DOWN;
	}
	else direction = MOVE_TYPE::IDEL;

	pixelCollision();
	run();
}

void Cmario::run()
{
	if (InputManager->isStayKeyDown('A'))
	{
		setSpeed(runSpeed);
		ANIMATION->findAnimation(str)->setFPS(runAniFrame);
	}
	else
	{
		setSpeed(speed);
		ANIMATION->findAnimation(str)->setFPS(aniFrame);
	}
}

void Cmario::animation()
{
	switch (direction)
	{
	case MOVE_TYPE::LEFT:
		strcpy(str, "마리오좌");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::RIGHT:
		strcpy(str, "마리오우");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::UP:
		strcpy(str, "마리오상");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::DOWN:
		strcpy(str, "마리오하");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::LEFTUP:
		strcpy(str, "마리오좌상");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::LEFTDOWN:
		strcpy(str, "마리오좌하");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::RIGHTUP:
		strcpy(str, "마리오우상");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::RIGHTDOWN:
		strcpy(str, "마리오우하");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::IDEL:
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->stop(str);
		break;
	default:
		break;
	}
}

void Cmario::pixelCollision()
{
	if (prevX != getX() || prevY != getY() + 20.0f)
	{
		if (m_sceneNum == 0b0000) 
		{
			COLORREF color = GetPixel(IMAGE->findImage("마을맵픽셀")->getMemDC(), getX(), getY() + 20.0f);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				setX(prevX);
				setY(prevY);
			}
		}
		else if (m_sceneNum == 0b0001)
		{
			COLORREF color = GetPixel(IMAGE->findImage("마리오집픽셀")->getMemDC(), getX(), getY());
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				setX(prevX);
				setY(prevY);
			}
		}
	}

	prevX = getX();
	prevY = getY();
}

void Cmario::attack()
{
}

void Cmario::item()
{
}

void Cmario::special()
{
}

void Cmario::etc()
{
}
