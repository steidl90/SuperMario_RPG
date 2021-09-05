#include "framework.h"
#include "CmarioBattle.h"

CmarioBattle::CmarioBattle() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("��������")), str("��������")
{
}

HRESULT CmarioBattle::init()
{
	setAtk(PLAYERDATA->getAtk());
	setDef(PLAYERDATA->getDef());
	setHp(PLAYERDATA->getHp());
	setMaxHp(PLAYERDATA->getMaxHp());
	setMp(PLAYERDATA->getMp());
	setMaxMp(PLAYERDATA->getMaxMp());
	setLv(PLAYERDATA->getLv());
	setExp(PLAYERDATA->getExp());
	setGold(PLAYERDATA->getGold());
	setSpeed(PLAYERDATA->getSpeed());
	setX(220);
	setY(510);
	setSceneNum(PLAYERDATA->getSceneNum());
	setBeforeSceneNum(PLAYERDATA->getBeforeSceneNum());
	setisFight(PLAYERDATA->getisFight());
    return S_OK;
}

void CmarioBattle::release()
{
}

void CmarioBattle::update()
{
	strcpy(str, "���������");
	direction = MOVE_TYPE::IDEL;
	animation();

	m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("�������̵�")->getFrameWidth() - 20, IMAGE->findImage("�������̵�")->getFrameHeight() - 20);
}

void CmarioBattle::render()
{
	ZORDER->zorderAniRender(IMAGE->findImage("�������̵�"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
}

void CmarioBattle::animation()
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

void CmarioBattle::move()
{
}

void CmarioBattle::attack()
{
}
