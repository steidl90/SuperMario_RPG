#include "framework.h"
#include "CsceneBattle.h"
#include "CsceneBanditsWay.h"
#include "Cmario.h"

CsceneBattle::CsceneBattle() :m_battle(new Cbattle), m_playerM(new CplayerManager), m_monsterM(new CmonsterManager), m_type(CHARACTER_TYPE::GOOMBA_BATTLE),
m_x(PLAYERDATA->getX()), m_y(PLAYERDATA->getY())
{
}

CsceneBattle::~CsceneBattle()
{
}

HRESULT CsceneBattle::init()
{
    m_battle = new Cbattle;
    m_playerM = new CplayerManager;
    m_monsterM = new CmonsterManager;

    m_x = PLAYERDATA->getX();
    m_y = PLAYERDATA->getY();

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

    setMonsterType();

    m_monsterM->init();

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
    if (m_playerM->getMarioBattle()->getFSM()->getstate() == STATE_TYPE::RUN)
    {
        m_playerM->getMario()->setSceneNum(0b0010);
        m_playerM->getMario()->setBeforeSceneNum(0b0010);
        m_playerM->getMario()->setisFight(false);
        PLAYERDATA->setData(m_playerM->getMario()->getAtk(),
            m_playerM->getMario()->getDef(),
            m_playerM->getMario()->getHp(),
            m_playerM->getMario()->getMaxHp(),
            m_playerM->getMario()->getMp(),
            m_playerM->getMario()->getMaxMp(),
            m_playerM->getMario()->getLv(),
            m_playerM->getMario()->getExp(),
            m_playerM->getMario()->getGold(),
            m_playerM->getMario()->getSpeed(),
            m_x,
            m_y,
            m_playerM->getMario()->getSceneNum(),
            m_playerM->getMario()->getBeforeSceneNum(),
            m_playerM->getMario()->getisFight());
        SCENE->changeScene("µµµÏ·Îµå");
    }
}

void CsceneBattle::setMonsterType()
{
    CsceneBanditsWay* scene = dynamic_cast<CsceneBanditsWay*>(SCENE->Find("µµµÏ·Îµå"));

    m_type = scene->getMonsterManager()->getType();

    scene->release();

    if (m_type == CHARACTER_TYPE::GOOMBA_WORLD)
    {
        for (int i = 0; i < 3; i++)
        {
            m_monsterM->addMonster(CHARACTER_TYPE::GOOMBA_BATTLE, 580 + (i * 140), 320 + (i * 80));
        }
    }
    else if (m_type == CHARACTER_TYPE::SKYTROOPA_WORLD)
    {
        for (int i = 0; i < 3; i++)
        {
            m_monsterM->addMonster(CHARACTER_TYPE::SKYTROOPA_BATTLE, 580 + (i * 140), 320 + (i * 80));
        }
    }
    else if (m_type == CHARACTER_TYPE::SPIKEY_WORLD)
    {
        for (int i = 0; i < 3; i++)
        {
            m_monsterM->addMonster(CHARACTER_TYPE::SPIKEY_BATTLE, 580 + (i * 140), 320 + (i * 80));
        }
    }


}
