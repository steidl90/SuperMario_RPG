#include "framework.h"
#include "CmarioBattle.h"
#include "CmonsterWorld.h"
#include "CmonsterManager.h"

CmarioBattle::CmarioBattle() :direction(MOVE_TYPE::IDEL), m_ani(ANIMATION->findAnimation("마리오하")), str("마리오우상"), m_FSM(new CFSMController), m_UI(new CmarioBattleUi), monsterNum(0),
m_monster(nullptr), curMotion(ATTACK_MOTION::READY), timer(TIME->getWorldTime()), isAttack(true), m_die(ANIMATION->findAnimation("사망"))
{
}

HRESULT CmarioBattle::init()
{
	m_FSM = new CFSMController;
	m_FSM->initState(this, CHARACTER_TYPE::PLAYER_BATTLE);

	m_monster = nullptr;
	monsterNum = 0;
	timer = TIME->getWorldTime();
	isAttack = true;
	curMotion = ATTACK_MOTION::READY;

	m_die = ANIMATION->findAnimation("사망");

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
	setNum(1);

	strcpy(str, "마리오우상");
	direction = MOVE_TYPE::IDEL;

	m_UI = new CmarioBattleUi;
	m_UI->init();

    return S_OK;
}

void CmarioBattle::release()
{
	SAFE_DELETE(m_FSM);
	SAFE_DELETE(m_UI);
}

void CmarioBattle::update()
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
		else if(m_monster->getY() + 85 > getY())
			setY(getY() + 1.0f);
		break;
	}
	case ATTACK_MOTION::ATTACK:
		direction = MOVE_TYPE::ATTACK;
		break;
	case ATTACK_MOTION::RETURN:
		setX(220);
		setY(510);
		curMotion = ATTACK_MOTION::READY;
		direction = MOVE_TYPE::IDEL;
		SEQUENCE->remover();
		m_FSM->getAI()->changeState(STATE_TYPE::IDLE);

		//m_monsterM->getVecMonster()->erase(m_monsterM->getVecMonster()->begin() + monsterNum);
		break;
	}

	animation();

	m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("마리오이동")->getFrameWidth() - 20, IMAGE->findImage("마리오이동")->getFrameHeight() - 20);
	
	m_UI->update();
}

void CmarioBattle::render()
{
	if (direction == MOVE_TYPE::ATTACK)
	{
		ZORDER->zorderAniRender(IMAGE->findImage("마리오공격"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
	}
	else
		ZORDER->zorderAniRender(IMAGE->findImage("마리오이동"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);

	if (m_FSM->getstate() != STATE_TYPE::IDLE && curMotion == ATTACK_MOTION::READY) action();

	m_UI->render(getHp(), getMaxHp());
}

void CmarioBattle::attack()
{

}

void CmarioBattle::animation()
{
	switch (direction)
	{
	case MOVE_TYPE::IDEL:
		strcpy(str, "마리오우상");
		m_ani = ANIMATION->findAnimation(str);
		ANIMATION->stop(str);
		break;
	case MOVE_TYPE::ATTACK:
		strcpy(str, "마리오기본공격");
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

void CmarioBattle::action()
{
	if (m_FSM->getstate() == STATE_TYPE::ITEM)
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 2, m_rc.left - 17, m_rc.top - 40, 1, 1); //X
	else
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 1, m_rc.left - 17, m_rc.top - 40, 1, 0); //X

	if (m_FSM->getstate() == STATE_TYPE::SKILL)
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 1, m_rc.left - 70, m_rc.top - 7, 0, 1); //Y
	else
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 1, m_rc.left - 70, m_rc.top - 7, 0, 0); //Y

	if (m_FSM->getstate() == STATE_TYPE::ATTACK)
	{
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 1, m_rc.left + 35, m_rc.top - 7, 2, 1); //A

		ZORDER->zorderAlphaRender(IMAGE->findImage("블랙스몰"), ZABOVEMAP, m_rc.bottom, m_rc.left + 500, m_rc.top + 150, 100);
		ZORDER->zorderRender(IMAGE->findImage("공격UI"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 500, m_rc.top + 150);
		ZORDER->zorderRender(IMAGE->findImage("기본공격글자"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 520, m_rc.top + 197);
		if (m_monster->getMonsterType() == CHARACTER_TYPE::GOOMBA_BATTLE) ZORDER->zorderRender(IMAGE->findImage("굼바글자"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 520, m_rc.top + 167);
		else if (m_monster->getMonsterType() == CHARACTER_TYPE::SKYTROOPA_BATTLE) ZORDER->zorderRender(IMAGE->findImage("날개거북이글자"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 520, m_rc.top + 167);
		else if (m_monster->getMonsterType() == CHARACTER_TYPE::SPIKEY_BATTLE) ZORDER->zorderRender(IMAGE->findImage("가시돌이글자"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 520, m_rc.top + 167);
	}
	else
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 1, m_rc.left + 35, m_rc.top - 7, 2, 0); //A

	if (m_FSM->getstate() == STATE_TYPE::ETC)
	{
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 2, m_rc.left - 17, m_rc.top + 27, 3, 1); //B
		ZORDER->zorderAlphaRender(IMAGE->findImage("블랙스몰"), ZABOVEMAP, m_rc.bottom, m_rc.left + 500, m_rc.top + 150, 100);

		if (InputManager->isToggleKey(VK_UP) || InputManager->isToggleKey(VK_DOWN))
		{
			ZORDER->zorderRender(IMAGE->findImage("도망"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 500, m_rc.top + 150);
			ZORDER->zorderAlphaRender(IMAGE->findImage("선택바"), ZABOVEMAP, m_rc.bottom, m_rc.left + 504, m_rc.top + 195, 200);
		}
		else
		{
			ZORDER->zorderRender(IMAGE->findImage("방어"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 500, m_rc.top + 150);
			ZORDER->zorderAlphaRender(IMAGE->findImage("선택바"), ZABOVEMAP, m_rc.bottom, m_rc.left + 504, m_rc.top + 165, 200);
		}
	}
	else
		ZORDER->zorderFrameRender(IMAGE->findImage("배틀버튼"), ZUNIT, m_rc.bottom + 1, m_rc.left - 17, m_rc.top + 27, 3, 0); //B
}

void CmarioBattle::move()
{
}

void CmarioBattle::monsterSelect()
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


