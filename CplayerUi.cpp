#include "framework.h"
#include "CplayerUi.h"
#include "Cplayer.h"

CplayerUi::CplayerUi() :m_timer(0.0f), isLevelUp(false)
{
}

CplayerUi::~CplayerUi()
{
}

HRESULT CplayerUi::init()
{
	m_currentLv = m_player->getLv();

	m_hpBar = new CprogressBar;
	m_hpBar->init("images/hp.bmp", "images/hp_back.bmp", 80, 20, 238, 10);
	m_hpBar->setGauge(m_player->getHp(), m_player->getMaxHp());

	m_hpBarSecond = new CprogressBar;
	m_hpBarSecond->init("images/hp.bmp", "images/hp_back.bmp", m_player->getPlayerX(), m_player->getPlayerY(), 33, 5);
	m_hpBarSecond->setGauge(m_player->getHp(), m_player->getMaxHp());

	m_mpBar = new CprogressBar;
	m_mpBar->init("images/mp.bmp", "images/hp_back.bmp", 80, 40, 196, 10);
	m_mpBar->setGauge(m_player->getMp(), m_player->getMaxMp());

	m_expBar = new CprogressBar;
	m_expBar->init("images/exp.bmp", "images/hp_back.bmp", 110, WINSIZEY - 115, 200, 10);
	m_expBar->setGauge(m_player->getExp(), m_player->getMaxExp());

	return S_OK;
}

void CplayerUi::release()
{
	SAFE_DELETE(m_hpBar);
	SAFE_DELETE(m_hpBarSecond);
	SAFE_DELETE(m_mpBar);
	SAFE_DELETE(m_expBar);
}

void CplayerUi::update()
{
	progressBarUpdate();

	if (m_currentLv < m_player->getLv())
	{
		m_currentLv = m_player->getLv();
		isLevelUp = true;
		m_timer = TIME->getWorldTime();
	}
	if (m_timer + 3 < TIME->getWorldTime()) isLevelUp = false;
}
//TODO::미니맵 UI 설정
void CplayerUi::render()
{
	progressBarRender();
	IMAGE->findImage("SkillUi")->render(getMemDC(), 0, (WINSIZEY - 39) - IMAGE->findImage("SkillUi")->getHeight());
	IMAGE->findImage("StateUi")->render(getMemDC(), 0, 0);
	IMAGE->findImage("MiniMapUi")->render(getMemDC(), (WINSIZEX - 15) - IMAGE->findImage("MiniMapUi")->getWidth(), 0);
	IMAGE->findImage("스킬Q")->render(getMemDC(), 143, (WINSIZEY - 56) - IMAGE->findImage("스킬Q")->getHeight());
	if (m_player->getLv() < 3) IMAGE->findImage("스킬잠금")->render(getMemDC(), 185, (WINSIZEY - 56) - IMAGE->findImage("스킬잠금")->getHeight());
	else IMAGE->findImage("스킬W")->render(getMemDC(), 185, (WINSIZEY - 56) - IMAGE->findImage("스킬W")->getHeight());
	if (m_player->getLv() < 7) IMAGE->findImage("스킬잠금")->render(getMemDC(), 227, (WINSIZEY - 56) - IMAGE->findImage("스킬잠금")->getHeight());
	else IMAGE->findImage("스킬E")->render(getMemDC(), 227, (WINSIZEY - 56) - IMAGE->findImage("스킬E")->getHeight());
	if (m_player->getLv() < 10) IMAGE->findImage("스킬잠금")->render(getMemDC(), 269, (WINSIZEY - 56) - IMAGE->findImage("스킬잠금")->getHeight());
	else IMAGE->findImage("스킬R")->render(getMemDC(), 269, (WINSIZEY - 56) - IMAGE->findImage("스킬R")->getHeight());

	IMAGE->findImage("플레이어체력바")->render(getMapDC(), m_player->getPlayerX() - 7, m_player->getPlayerY() - 10);

	if (isLevelUp)
	{
		IMAGE->findImage("레벨업")->render(getMemDC(), WINSIZEX / 2 - 145, WINSIZEY / 2 - 190);

		TCHAR strLv[20];
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		SetTextAlign(getMemDC(), TA_CENTER);
		sprintf_s(strLv, "레벨업 Lv:%d", m_player->getLv());
		TextOut(getMemDC(), WINSIZEX / 2 - 7, WINSIZEY / 2 - 163, strLv, strlen(strLv));
		SetTextAlign(getMemDC(), TA_LEFT);
	}

	playerStateRender();

}

void CplayerUi::progressBarUpdate()
{
	m_hpBar->update();
	m_hpBar->setGauge(m_player->getHp(), m_player->getMaxHp());
	m_hpBarSecond->mapUpdate(m_player->getPlayerX() + 1, m_player->getPlayerY() - 3);
	m_hpBarSecond->setGauge(m_player->getHp(), m_player->getMaxHp());
	m_mpBar->update();
	m_mpBar->setGauge(m_player->getMp(), m_player->getMaxMp());
	m_expBar->update();
	m_expBar->setGauge(m_player->getExp(), m_player->getMaxExp());
}

void CplayerUi::progressBarRender()
{
	m_hpBar->render();
	m_hpBarSecond->mapRender();
	m_mpBar->render();
	m_expBar->render();
}

void CplayerUi::playerStateRender()
{
	// Player Level 좌상단 표시
	TCHAR str[20];
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetTextAlign(getMemDC(), TA_CENTER);
	sprintf_s(str, "%d", m_player->getLv());
	TextOut(getMemDC(), 36, 75, str, strlen(str));
	SetTextAlign(getMemDC(), TA_LEFT);

	// Player 현재, 최대 Hp,Mp 표시 
	TCHAR strhp[128];
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	sprintf_s(strhp, "%d/%d", m_player->getHp(), m_player->getMaxHp());
	TextOut(getMemDC(), 165, 17, strhp, strlen(strhp));
	sprintf_s(strhp, "%d/%d", m_player->getMp(), m_player->getMaxMp());
	TextOut(getMemDC(), 155, 37, strhp, strlen(strhp));
}
