#include "framework.h"
#include "CbowserBattle.h"

CbowserBattle::CbowserBattle() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하")), str("피치대기"), m_FSM(new CFSMController)
{
}

HRESULT CbowserBattle::init()
{
    m_FSM = new CFSMController;
    m_FSM->initState(this, CHARACTER_TYPE::PLAYER_BATTLE);

    setX(420);
    setY(605);
    setNum(3);

    return S_OK;
}

void CbowserBattle::release()
{
    SAFE_DELETE(m_FSM);
}

void CbowserBattle::update()
{
    direction = MOVE_TYPE::IDEL;
    animation();
    m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("쿠파대기")->getFrameWidth() - 20, IMAGE->findImage("쿠파대기")->getFrameHeight() - 20);
    m_FSM->updateState();
}

void CbowserBattle::render()
{
    ZORDER->zorderRender(IMAGE->findImage("쿠파대기"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15);
    //ZORDER->zorderAniRender(IMAGE->findImage("쿠파대기"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
    if (m_FSM->getstate() != STATE_TYPE::IDLE)action();
}

void CbowserBattle::animation()
{
    switch (direction)
    {
    case MOVE_TYPE::IDEL:

        break;
    }
}

void CbowserBattle::action()
{
}

void CbowserBattle::move()
{
}

void CbowserBattle::attack()
{
}
