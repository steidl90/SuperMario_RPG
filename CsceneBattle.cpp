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
    m_playerM->getMarioBattle()->setAtk(PLAYERDATA->getAtk());
    m_playerM->getMarioBattle()->setDef(PLAYERDATA->getDef());
    m_playerM->getMarioBattle()->setHp(PLAYERDATA->getHp());
    m_playerM->getMarioBattle()->setMaxHp(PLAYERDATA->getMaxHp());
    m_playerM->getMarioBattle()->setMp(PLAYERDATA->getMp());
    m_playerM->getMarioBattle()->setMaxMp(PLAYERDATA->getMaxMp());
    m_playerM->getMarioBattle()->setLv(PLAYERDATA->getLv());
    m_playerM->getMarioBattle()->setExp(PLAYERDATA->getExp());
    m_playerM->getMarioBattle()->setGold(PLAYERDATA->getGold());
    m_playerM->getMarioBattle()->setSpeed(PLAYERDATA->getSpeed());
    m_playerM->getMarioBattle()->setX(220);
    m_playerM->getMarioBattle()->setY(510);
    m_playerM->getMarioBattle()->setSceneNum(PLAYERDATA->getSceneNum());
    m_playerM->getMarioBattle()->setisFight(PLAYERDATA->getisFight());
    m_playerM->getMario()->setisFight(PLAYERDATA->getisFight());

    m_monsterM->setPlayerBattleMemory(m_playerM->getMarioBattle());

    setMonsterType();

    m_monsterM->init();

    m_playerM->getMarioBattle()->setMonsterManagerMemory(m_monsterM);

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

    if (SEQUENCE->getVecSequence().size() == 0)
    {
        for (int i = 0; i < m_playerM->getVecPlayer()->size() - 2; i++)
        {
            SEQUENCE->pushSequence((*m_playerM->getVecPlayer())[i]->getNum());
        }
        for (int i = 0; i < m_monsterM->getVecMonster()->size(); i++)
        {
            SEQUENCE->pushSequence((*m_monsterM->getVecMonster())[i]->getNum());
        }
    }
    
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
    if (m_playerM->getMarioBattle()->getFSM()->getstate() == STATE_TYPE::RUN || m_monsterM->getVecMonster()->size() == 0)
    {
        m_playerM->getMarioBattle()->setSceneNum(0b0010);
        m_playerM->getMarioBattle()->setBeforeSceneNum(0b0010);
        m_playerM->getMarioBattle()->setisFight(false);
        initSequence();
        PLAYERDATA->setData(m_playerM->getMarioBattle()->getAtk(),
            m_playerM->getMarioBattle()->getDef(),
            m_playerM->getMarioBattle()->getHp(),
            m_playerM->getMarioBattle()->getMaxHp(),
            m_playerM->getMarioBattle()->getMp(),
            m_playerM->getMarioBattle()->getMaxMp(),
            m_playerM->getMarioBattle()->getLv(),
            m_playerM->getMarioBattle()->getExp(),
            m_playerM->getMarioBattle()->getGold(),
            m_playerM->getMarioBattle()->getSpeed(),
            m_x,
            m_y,
            m_playerM->getMarioBattle()->getSceneNum(),
            m_playerM->getMarioBattle()->getBeforeSceneNum(),
            m_playerM->getMarioBattle()->getisFight());
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

void CsceneBattle::initSequence()
{
    for (int i = 0; i < SEQUENCE->getVecSequence().size() + i; i++)
    {
        SEQUENCE->remover();
    }

}
