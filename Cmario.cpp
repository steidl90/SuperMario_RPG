#include "framework.h"
#include "Cmario.h"
#include "Cstate.h"
#include "CFSM.h"
#include "CmarioState.h"

Cmario::Cmario() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하"))
{
}

Cmario::Cmario(float x, float y, RECT rc, stats stats) :
    Ccharacter(x, y, rc, stats), direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하"))
{
    m_x = x;
    m_y = y;
    m_rc = rc;
    m_stats.atk = stats.atk;
    m_stats.def = stats.def;
    m_stats.exp = stats.exp;
    m_stats.gold = stats.gold;
    m_stats.hp = stats.hp;
    m_stats.lv = stats.lv;
    m_stats.mp = stats.mp;
    m_stats.speed = stats.speed;
}

Cmario::~Cmario()
{
}

HRESULT Cmario::init()
{
    m_x = WINSIZEX / 2;
    m_y = WINSIZEY / 2;
    m_stats.lv = 1;
    m_stats.atk = 10;
    m_stats.def = 10;
    m_stats.hp = 30;
    m_stats.mp = 10;
    m_stats.exp = 10;
    m_stats.gold = 0;
    m_stats.speed = 3.0f;

    setLv(m_stats.lv);
    setAtk(m_stats.atk);
    setDef(m_stats.def);
    setHp(m_stats.hp);
    setMp(m_stats.mp);
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
    if (getstate() == STATE_TYPE::STATE_TYPE_IDLE || getstate() == STATE_TYPE::STATE_TYPE_TRACE)
    {
        move();
        animation();
    }
    m_rc = RectMake(m_x, m_y, IMAGE->findImage("마리오이동")->getFrameWidth() - 20, IMAGE->findImage("마리오이동")->getFrameHeight() - 20);

    updateAI();
}

void Cmario::render()
{
    //Rectangle(getMemDC(), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
    //IMAGE->findImage("마리오이동")->frameRender(getMemDC(), m_x, m_y);
    IMAGE->findImage("마리오이동")->aniRender(getMemDC(), m_rc.left - 10, m_rc.top - 15, m_ani);
}

void Cmario::move()
{
    if (InputManager->isStayKeyDown(VK_RIGHT) && InputManager->isStayKeyDown(VK_DOWN))
    {
        direction = MOVE_TYPE::RIGHTDOWN;
    }
    else if (InputManager->isStayKeyDown(VK_RIGHT) && InputManager->isStayKeyDown(VK_UP))
    {
        direction = MOVE_TYPE::RIGHTUP;
    }
    else if (InputManager->isStayKeyDown(VK_LEFT) && InputManager->isStayKeyDown(VK_DOWN))
    {
        direction = MOVE_TYPE::LEFTDOWN;
    }
    else if (InputManager->isStayKeyDown(VK_LEFT) && InputManager->isStayKeyDown(VK_UP))
    {
        direction = MOVE_TYPE::LEFTUP;
    }
    else if (InputManager->isStayKeyDown(VK_LEFT))
    {
        direction = MOVE_TYPE::LEFT;
    }
    else if (InputManager->isStayKeyDown(VK_RIGHT))
    {
        direction = MOVE_TYPE::RIGHT;
    }
    else if (InputManager->isStayKeyDown(VK_UP))
    {
        direction = MOVE_TYPE::UP;
    }
    else if (InputManager->isStayKeyDown(VK_DOWN))
    {
        direction = MOVE_TYPE::DOWN;
    }
    else
    {

    }
}

void Cmario::animation()
{
    switch (direction)
    {
    case MOVE_TYPE::LEFT:
        setX(getX() - getSpeed());
        m_ani = ANIMATION->findAnimation("마리오좌");
        ANIMATION->resume("마리오좌");
        break;
    case MOVE_TYPE::RIGHT:
        setX(getX() + getSpeed());
        m_ani = ANIMATION->findAnimation("마리오우");
        ANIMATION->resume("마리오우");
        break;
    case MOVE_TYPE::UP:
        setY(getY() - getSpeed());
        m_ani = ANIMATION->findAnimation("마리오상");
        ANIMATION->resume("마리오상");
        break;
    case MOVE_TYPE::DOWN:
        setY(getY() + getSpeed());
        m_ani = ANIMATION->findAnimation("마리오하");
        ANIMATION->resume("마리오하");
        break;
    case MOVE_TYPE::LEFTUP:
        setX(getX() - getSpeed() * 0.75);
        setY(getY() - getSpeed() * 0.75);
        m_ani = ANIMATION->findAnimation("마리오좌상");
        ANIMATION->resume("마리오좌상");
        break;
    case MOVE_TYPE::LEFTDOWN:
        setX(getX() - getSpeed() * 0.75);
        setY(getY() + getSpeed() * 0.75);
        m_ani = ANIMATION->findAnimation("마리오좌하");
        ANIMATION->resume("마리오좌하");
        break;
    case MOVE_TYPE::RIGHTUP:
        setX(getX() + getSpeed() * 0.75);
        setY(getY() - getSpeed() * 0.75);
        m_ani = ANIMATION->findAnimation("마리오우상");
        ANIMATION->resume("마리오우상");
        break;
    case MOVE_TYPE::RIGHTDOWN:
        setX(getX() + getSpeed() * 0.75);
        setY(getY() + getSpeed() * 0.75);
        m_ani = ANIMATION->findAnimation("마리오우하");
        ANIMATION->resume("마리오우하");
        break;
    default:
        break;
    }
}
