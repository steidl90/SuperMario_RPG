#include "framework.h"
#include "Cmario.h"
#include "Cstate.h"
#include "CmarioState.h"

Cmario::Cmario() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("��������")), str("��������"), prevX(0.0f), prevY(0.0f), m_sceneNum(0)
{
}

Cmario::Cmario(float x, float y, RECT rc, stats stats) :
	Cunit(x, y, rc, stats), direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("��������")), str("��������")
{

}

Cmario::~Cmario()
{
}

HRESULT Cmario::init()
{
	m_x = WINSIZEX / 2 + 50;
	m_y = WINSIZEY / 2 + 500;
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
	setisFight(false);
	m_FSM = new CFSMController;
	m_FSM->initState(this, CHARACTER_TYPE::PLAYER_WORLD);
	return S_OK;
}

void Cmario::release()
{
}

void Cmario::update()
{
	move();
	animation();
	m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("�������̵�")->getFrameWidth() - 20, IMAGE->findImage("�������̵�")->getFrameHeight() - 20);

}

void Cmario::render()
{
	if (InputManager->isToggleKey(VK_TAB))Rectangle(getMapDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
	ZORDER->zorderAniRender(IMAGE->findImage("�������̵�"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);

	
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
		strcpy(str, "��������");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::RIGHT:
		strcpy(str, "��������");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::UP:
		strcpy(str, "��������");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::DOWN:
		strcpy(str, "��������");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::LEFTUP:
		strcpy(str, "�������»�");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::LEFTDOWN:
		strcpy(str, "����������");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::RIGHTUP:
		strcpy(str, "���������");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->resume(str);
		break;
	case MOVE_TYPE::RIGHTDOWN:
		strcpy(str, "����������");
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
			COLORREF color = GetPixel(IMAGE->findImage("�������ȼ�")->getMemDC(), getX(), getY() + 20.0f);
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
			COLORREF color = GetPixel(IMAGE->findImage("���������ȼ�")->getMemDC(), getX(), getY() + 20.0f);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				setX(prevX);
				setY(prevY);
			}
		}
		/*else if (m_sceneNum == 0b0010)
		{
			COLORREF color = GetPixel(IMAGE->findImage("�ʵ��1�ȼ�")->getMemDC(), getX(), getY() + 20.0f);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (!(r == 255 && g == 0 && b == 255))
			{
				setX(prevX);
				setY(prevY);
			}
		}*/
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
