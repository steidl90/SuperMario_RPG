#include "framework.h"
#include "CsceneBattle.h"

CsceneBattle::CsceneBattle() :m_battle(new Cbattle), m_playerM(new CplayerManager), m_monsterM(new CmonsterManager)
{
}

HRESULT CsceneBattle::init()
{
    m_playerM->init();
    m_playerM->getMario()->setAtk(PLAYERDATA->getAtk());
    m_playerM->getMario()->setDef(PLAYERDATA->getDef());
    m_playerM->getMario()->setHp(PLAYERDATA->getHp());
    m_playerM->getMario()->setMaxHp(PLAYERDATA->getMaxHp());
    m_playerM->getMario()->setMp(PLAYERDATA->getMp());
    m_playerM->getMario()->setMaxMp(PLAYERDATA->getMaxMp());
    m_playerM->getMario()->setLv(PLAYERDATA->getLv());
    m_playerM->getMario()->setExp(PLAYERDATA->getExp());
    m_playerM->getMario()->setGold(PLAYERDATA->getGold());
    m_playerM->getMario()->setSpeed(PLAYERDATA->getSpeed());
    m_playerM->getMario()->setX(220);
    m_playerM->getMario()->setY(510);
    m_playerM->getMario()->setSceneNum(PLAYERDATA->getSceneNum());
    m_playerM->getMario()->setisFight(PLAYERDATA->getisFight());

    m_monsterM->setPlayerMemory(m_playerM->getMario());

    m_monsterM->init();

    return S_OK;
}

void CsceneBattle::release()
{
}

void CsceneBattle::update()
{
    m_playerM->update();
    m_monsterM->update();

    scenechange();
}

void CsceneBattle::render()
{
    this->getMapBuffer()->render(getMemDC(), 0, 0);

    m_battle->render();
    m_playerM->render();
    m_monsterM->render();

    ZORDER->zorderTotalRender(getMapDC());
}

void CsceneBattle::scenechange()
{
}
