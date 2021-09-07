#include "framework.h"
#include "CmarioBattle.h"

CmarioBattle::CmarioBattle() :direction(MOVE_TYPE::DOWN), m_ani(ANIMATION->findAnimation("��������")), str("��������"), m_FSM(new CFSMController), m_UI(new CmarioBattleUi)
{
}

HRESULT CmarioBattle::init()
{
	m_FSM = new CFSMController;
	m_FSM->initState(this, CHARACTER_TYPE::PLAYER_BATTLE);
	
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
	strcpy(str, "���������");
	direction = MOVE_TYPE::IDEL;
	animation();

	m_rc = RectMakeCenter(getX(), getY(), IMAGE->findImage("�������̵�")->getFrameWidth() - 20, IMAGE->findImage("�������̵�")->getFrameHeight() - 20);

	m_FSM->updateState();
	m_UI->update();
}

void CmarioBattle::render()
{
	ZORDER->zorderAniRender(IMAGE->findImage("�������̵�"), ZUNIT, m_rc.bottom, m_rc.left - 10, m_rc.top - 15, m_ani);
	if (m_FSM->getstate() != STATE_TYPE::IDLE)action();

	m_UI->render();
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

void CmarioBattle::action()
{
	if (m_FSM->getstate() == STATE_TYPE::ITEM) 
		ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 17, m_rc.top - 40, 1, 1); //X
	else
		ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 17, m_rc.top - 40, 1, 0); //X

	if (m_FSM->getstate() == STATE_TYPE::SKILL)
		ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 70, m_rc.top - 7, 0, 1); //Y
	else 
		ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 70, m_rc.top - 7, 0, 0); //Y

	if (m_FSM->getstate() == STATE_TYPE::ATTACK)
	{
		ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left + 35, m_rc.top - 7, 2, 1); //A

		ZORDER->zorderAlphaRender(IMAGE->findImage("������"), ZABOVEMAP, m_rc.bottom, m_rc.left + 500, m_rc.top + 150, 100);
		ZORDER->zorderRender(IMAGE->findImage("����UI"), ZABOVEMAP, m_rc.bottom + 1, m_rc.left + 500, m_rc.top + 150);
	}
	else 
		ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left + 35, m_rc.top - 7, 2, 0); //A

	if (m_FSM->getstate() == STATE_TYPE::ETC) 
	{
		ZORDER->zorderFrameRender(IMAGE->findImage("��Ʋ��ư"), ZUNIT, m_rc.bottom + 1, m_rc.left - 17, m_rc.top + 27, 3, 1); //B
		ZORDER->zorderAlphaRender(IMAGE->findImage("������"), ZABOVEMAP, m_rc.bottom, m_rc.left + 500, m_rc.top + 150, 100);

		// ????????????????
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

void CmarioBattle::move()
{
}

void CmarioBattle::attack()
{
}
