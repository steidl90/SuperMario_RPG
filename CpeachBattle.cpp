#include "framework.h"
#include "CpeachBattle.h"

CpeachBattle::CpeachBattle():direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하")), str("피치대기"), m_FSM(new CFSMController)
{
}

HRESULT CpeachBattle::init()
{
    m_FSM = new CFSMController;
    m_FSM->initState(this, CHARACTER_TYPE::PLAYER_BATTLE);

	setX(305);
	setY(550);
    setNum(2);

    return S_OK;
}

void CpeachBattle::release()
{
    SAFE_DELETE(m_FSM);
}

void CpeachBattle::update()
{
    direction = MOVE_TYPE::IDEL;
    animation();
    m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("피치대기")->getFrameWidth() - 20, IMAGE->findImage("피치대기")->getFrameHeight() - 20);
    m_FSM->updateState();
}

void CpeachBattle::render()
{
    ZORDER->zorderRender(IMAGE->findImage("피치대기"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15);
    //ZORDER->zorderAniRender(IMAGE->findImage("피치대기"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
    if (m_FSM->getstate() != STATE_TYPE::IDLE)action();
}

void CpeachBattle::animation()
{
	switch (direction)
	{
	case MOVE_TYPE::IDEL:

		break;
	}
}

void CpeachBattle::action()
{
}

void CpeachBattle::move()
{
}

void CpeachBattle::attack()
{
}
