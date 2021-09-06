#include "framework.h"
#include "CsceneBattle.h"
#include "Cmario.h"

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

    for (int i = 0; i < 2; i++)
    {
        m_monsterM->addMonster(CHARACTER_TYPE::MONSTER_WORLD, 580 + (i * 250), 680 - (i * 100));
    }

    m_monsterM->addMonster(CHARACTER_TYPE::SKYTROOPA_WORLD, 400, 380);

    for (int i = 0; i < 2; i++)
    {
        m_monsterM->addMonster(CHARACTER_TYPE::SPIKEY_WORLD, 900 - (i * 500), 830 - (i * 70));
    }

    m_monsterM->init(m_playerM->getMario());

    return S_OK;
}

void CsceneBattle::release()
{
    SAFE_DELETE(m_battle);
    SAFE_DELETE(m_playerM);
    SAFE_DELETE(m_monsterM);
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
