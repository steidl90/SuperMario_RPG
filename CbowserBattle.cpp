#include "framework.h"
#include "CbowserBattle.h"
#include "CmonsterWorld.h"
#include "CmonsterManager.h"

CbowserBattle::CbowserBattle() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("��������")), str("��ġ���"), m_FSM(new CFSMController)
{
}

HRESULT CbowserBattle::init()
{
    m_FSM = new CFSMController;
    m_FSM->initState(this, CHARACTER_TYPE::PLAYER_BATTLE);

    m_monster = nullptr;
    timer = TIME->getWorldTime();
    isAttack = true;
    curMotion = ATTACK_MOTION::READY;

    m_die = ANIMATION->findAnimation("���");

    direction = MOVE_TYPE::IDEL;

    setX(420);
    setY(605);
    setNum(RND->getFromIntTo(2, 100000));
    setHp(45);
    setMaxHp(45);

    m_UI = new CbowserBattleUi;
    m_UI->init();

    return S_OK;
}

void CbowserBattle::release()
{
    SAFE_DELETE(m_FSM);
    SAFE_DELETE(m_UI);
}

void CbowserBattle::update()
{
    m_FSM->updateState();

    if (m_FSM->getstate() == STATE_TYPE::ATTACK)
    {
        monsterSelect();
        if (InputManager->isOnceKeyDown('S'))
        {
            curMotion = ATTACK_MOTION::MOVE;
        }
    }

    switch (curMotion)
    {
    case ATTACK_MOTION::READY:
        break;
    case ATTACK_MOTION::MOVE:
    {
        if (m_monster->getX() - 90 >= getX())
            setX(getX() + 20.0f);
        
        if (m_monster->getY() + 70 <= getY())
            setY(getY() - 8.0f);
        else
        {
            timer = TIME->getWorldTime();
            curMotion = ATTACK_MOTION::ATTACK;
        }

        break;
    }
    case ATTACK_MOTION::ATTACK:
        direction = MOVE_TYPE::ATTACK;
        break;
    case ATTACK_MOTION::RETURN:
        setX(420);
        setY(605);
        curMotion = ATTACK_MOTION::READY;
        direction = MOVE_TYPE::IDEL;
        SEQUENCE->remover();
        m_FSM->getAI()->changeState(STATE_TYPE::IDLE);
        //m_monsterM->getVecMonster()->erase(m_monsterM->getVecMonster()->begin() + monsterNum);
        break;
    }

    animation();

    m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("���Ĵ��")->getFrameWidth() - 20, IMAGE->findImage("���Ĵ��")->getFrameHeight() - 20);
   
    m_FSM->updateState();
}

void CbowserBattle::render()
{
    if (direction == MOVE_TYPE::ATTACK)
        ZORDER->zorderAniRender(IMAGE->findImage("���İ���"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
    else
        ZORDER->zorderRender(IMAGE->findImage("���Ĵ��"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15);

    if (m_FSM->getstate() != STATE_TYPE::IDLE && curMotion == ATTACK_MOTION::READY) action();

    m_UI->render(getHp(), getMaxHp());
}

void CbowserBattle::animation()
{
    switch (direction)
    {
    case MOVE_TYPE::IDEL:
        break;
    case MOVE_TYPE::ATTACK:
        strcpy(str, "���ı⺻����");
        m_ani = ANIMATION->findAnimation(str);
        ANIMATION->resume(str);
        if (timer + 0.8f <= TIME->getWorldTime())
        {
            curMotion = ATTACK_MOTION::RETURN;
            timer = TIME->getWorldTime();
            ANIMATION->stopAttack(str);
            m_monster->setHp(m_monster->getHp() - 15);
            ANIMATION->initAni(str);
        }
        break;
    }
}

void CbowserBattle::action()
{
    if (m_FSM->getstate() == STATE_TYPE::ITEM)
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 2, m_rc.left - 17, m_rc.top - 40, 1, 1); //X
    else
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 17, m_rc.top - 40, 1, 0); //X

    if (m_FSM->getstate() == STATE_TYPE::SKILL)
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 70, m_rc.top - 7, 0, 1); //Y
    else
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 70, m_rc.top - 7, 0, 0); //Y

    if (m_FSM->getstate() == STATE_TYPE::ATTACK)
    {
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left + 35, m_rc.top - 7, 2, 1); //A

        ZORDER->zorderAlphaRender(IMAGE->findImage("������"), ZABOVEMAP, m_rc.bottom, 700, 650, 100);
        ZORDER->zorderRender(IMAGE->findImage("����UI"), ZABOVEMAP, m_rc.bottom + 1, 700, 650);
        ZORDER->zorderRender(IMAGE->findImage("�⺻���ݱ���"), ZABOVEMAP, m_rc.bottom + 1, 720, 697);
        if (m_monster->getMonsterType() == CHARACTER_TYPE::GOOMBA_BATTLE) ZORDER->zorderRender(IMAGE->findImage("���ٱ���"), ZABOVEMAP, m_rc.bottom + 1, 720, 667);
        else if (m_monster->getMonsterType() == CHARACTER_TYPE::SKYTROOPA_BATTLE) ZORDER->zorderRender(IMAGE->findImage("�����ź��̱���"), ZABOVEMAP, m_rc.bottom + 1, 720, 667);
        else if (m_monster->getMonsterType() == CHARACTER_TYPE::SPIKEY_BATTLE) ZORDER->zorderRender(IMAGE->findImage("���õ��̱���"), ZABOVEMAP, m_rc.bottom + 1, 720, 667);
    }
    else
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left + 35, m_rc.top - 7, 2, 0); //A

    if (m_FSM->getstate() == STATE_TYPE::ETC)
    {
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 2, m_rc.left - 17, m_rc.top + 27, 3, 1); //B
        ZORDER->zorderAlphaRender(IMAGE->findImage("������"), ZABOVEMAP, m_rc.bottom, m_rc.left + 500, m_rc.top + 150, 100);

        if (InputManager->isToggleKey(VK_UP) || InputManager->isToggleKey(VK_DOWN))
        {
            ZORDER->zorderRender(IMAGE->findImage("����"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 500, m_rc.top + 150);
            ZORDER->zorderAlphaRender(IMAGE->findImage("���ù�"), ZABOVEMAP, m_rc.bottom, m_rc.left + 504, m_rc.top + 195, 200);
        }
        else
        {
            ZORDER->zorderRender(IMAGE->findImage("���"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 500, m_rc.top + 150);
            ZORDER->zorderAlphaRender(IMAGE->findImage("���ù�"), ZABOVEMAP, m_rc.bottom, m_rc.left + 504, m_rc.top + 165, 200);
        }
    }
    else
        ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 17, m_rc.top + 27, 3, 0); //B
}

void CbowserBattle::move()
{
}

void CbowserBattle::monsterSelect()
{
    auto iter = m_monsterM->getVecMonster()->begin();

    if (InputManager->isOnceKeyDown(VK_DOWN) || InputManager->isOnceKeyDown(VK_RIGHT))
        monsterNum++;
    else if (InputManager->isOnceKeyDown(VK_UP) || InputManager->isOnceKeyDown(VK_LEFT))
        monsterNum--;

    if (monsterNum >= static_cast<int>(m_monsterM->getVecMonster()->size()))
        monsterNum = 0;

    if (monsterNum < 0)
        monsterNum = m_monsterM->getVecMonster()->size() - 1;

    m_monster = dynamic_cast<CmonsterWorld*>(*(iter + monsterNum));

    ZORDER->zorderRender(IMAGE->findImage("����ȭ��ǥ"), ZEFFECT, 0, m_monster->getX() - 20, m_monster->getY() - 20);
}

void CbowserBattle::attack()
{
}
