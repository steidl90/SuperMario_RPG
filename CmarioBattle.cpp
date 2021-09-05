#include "framework.h"
#include "CmarioBattle.h"

CmarioBattle::CmarioBattle() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하")), str("마리오하")
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
	strcpy(str, "마리오우상");
	direction = MOVE_TYPE::IDEL;
	animation();

	m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("마리오이동")->getFrameWidth() - 20, IMAGE->findImage("마리오이동")->getFrameHeight() - 20);
}

void CmarioBattle::render()
{
	ZORDER->zorderAniRender(IMAGE->findImage("마리오이동"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
}

void CmarioBattle::animation()
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

void CmarioBattle::move()
{
}

void CmarioBattle::attack()
{
}
