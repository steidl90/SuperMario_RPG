#include "framework.h"
#include "CpeachBattle.h"
#include "CmonsterWorld.h"
#include "CmonsterManager.h"

CpeachBattle::CpeachBattle():direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("마리오하")), str("피치대기"), m_FSM(new CFSMController), m_UI(new CpeachBattleUi)
{
}

HRESULT CpeachBattle::init()
{
    m_FSM = new CFSMController;
    m_FSM->initState(this, CHARACTER_TYPE::PLAYER_BATTLE);

	m_monster = nullptr;
	timer = TIME->getWorldTime();
	isAttack = true;
	curMotion = ATTACK_MOTION::READY;

	m_die = ANIMATION->findAnimation("사망");

	direction = MOVE_TYPE::IDEL;

	setX(305);
	setY(550);
    setNum(2);
    setHp(35);
    setMaxHp(35);

	m_UI = new CpeachBattleUi;
	m_UI->init();

    return S_OK;
}

void CpeachBattle::release()
{
    SAFE_DELETE(m_FSM);
    SAFE_DELETE(m_UI);
}

void CpeachBattle::update()
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
		else
		{
			timer = TIME->getWorldTime();
			curMotion = ATTACK_MOTION::ATTACK;
		}

		if (m_monster->getY() + 85 <= getY())
			setY(getY() - 8.0f);
		else if (m_monster->getY() + 85 > getY())
			setY(getY() + 1.0f);
		break;
	}
	case ATTACK_MOTION::ATTACK:
		direction = MOVE_TYPE::ATTACK;
		break;
	case ATTACK_MOTION::RETURN:
		setX(305);
		setY(550);
		curMotion = ATTACK_MOTION::READY;
		direction = MOVE_TYPE::IDEL;
		SEQUENCE->remover();
		m_FSM->getAI()->changeState(STATE_TYPE::IDLE);
		//m_monsterM->getVecMonster()->erase(m_monsterM->getVecMonster()->begin() + monsterNum);
		break;
	}

    animation();

    m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("피치대기")->getFrameWidth() - 20, IMAGE->findImage("피치대기")->getFrameHeight() - 20);
    
	m_UI->update();
}

void CpeachBattle::render()
{
	if(direction == MOVE_TYPE::ATTACK)
		ZORDER->zorderRender(IMAGE->findImage("피치대기"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15);
	else
		ZORDER->zorderRender(IMAGE->findImage("피치대기"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15);

    if (m_FSM->getstate() != STATE_TYPE::IDLE && curMotion == ATTACK_MOTION::READY) action();

	m_UI->render(getHp(), getMaxHp());
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

void CpeachBattle::monsterSelect()
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

	ZORDER->zorderRender(IMAGE->findImage("선택화살표"), ZEFFECT, 0, m_monster->getX() - 20, m_monster->getY() - 20);
}

void CpeachBattle::attack()
{
}
