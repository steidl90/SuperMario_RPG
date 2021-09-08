#include "framework.h"
#include "CsceneBanditsWay.h"
#include "CmonsterWorld.h"

CsceneBanditsWay::CsceneBanditsWay()
    : m_banditsWay(new CbanditsWay), m_playerM(new CplayerManager), m_door(RectMake(0, 0, 0, 0)), m_monsterM(new CmonsterManager),
    m_monsterType()
{
}

CsceneBanditsWay::~CsceneBanditsWay()
{
}

HRESULT CsceneBanditsWay::init()
{
    m_banditsWay = new CbanditsWay;
    m_playerM = new CplayerManager;
    m_monsterM = new CmonsterManager;

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
    m_playerM->getMario()->setX(PLAYERDATA->getX());
    m_playerM->getMario()->setY(PLAYERDATA->getY());
    m_playerM->getMario()->setSceneNum(PLAYERDATA->getSceneNum());
    m_playerM->getMario()->setisFight(PLAYERDATA->getisFight());

    m_door = RectMake(220, 80, 50, 50);

    m_monsterM->setPlayerMemory(m_playerM->getMario());
    initMonster();

    return S_OK;
}

void CsceneBanditsWay::release()
{
    SAFE_DELETE(m_banditsWay);
    SAFE_DELETE(m_playerM);
    SAFE_DELETE(m_monsterM);
}

void CsceneBanditsWay::update()
{
    CAMERA->update();
    CAMERA->setTargetPoint(PointMake(m_playerM->getMarioRect()->left, m_playerM->getMarioRect()->top));
    m_banditsWay->update();
    m_playerM->update();
    m_monsterM->update();

    scenechange();
}

void CsceneBanditsWay::render()
{
    this->getMapBuffer()->render(getMemDC(), 0, 0, CAMERA->getCameraPoint().x, CAMERA->getCameraPoint().y, CAMERA->getCameraWidth(), CAMERA->getCameraHeight());

    m_banditsWay->render();
    m_playerM->render();
    m_monsterM->render();

    //Rectangle(getMapDC(), m_door.left, m_door.top, m_door.right, m_door.bottom);
    //if (InputManager->isToggleKey(VK_TAB)) ZORDER->zorderRender(IMAGE->findImage("���������ȼ�"), ZDEBUG, 0, 0, 0);

    if (InputManager->isToggleKey(VK_TAB))
    {
        ZORDER->zorderRectangle(*m_playerM->getMarioRect(), ZCOLMAP);
        ZORDER->zorderRectangle(m_door, ZDEBUG);
    }
    ZORDER->zorderTotalRender(getMapDC());
}

void CsceneBanditsWay::initMonster()
{
    for (int i = 0; i < 2; i++)
    {
        m_monsterM->addMonster(CHARACTER_TYPE::GOOMBA_WORLD, 580 + (i * 250), 680 - (i * 100));
    }

    m_monsterM->addMonster(CHARACTER_TYPE::SKYTROOPA_WORLD, 400, 380);

    for (int i = 0; i < 2; i++)
    {
        m_monsterM->addMonster(CHARACTER_TYPE::SPIKEY_WORLD, 900 - (i * 500), 900 - (i * 70));
    }

    m_monsterM->init();
}

void CsceneBanditsWay::scenechange()
{
    RECT temp;
    for (m_viMonster = m_monsterM->getVecMonster()->begin(); m_viMonster != m_monsterM->getVecMonster()->end(); ++m_viMonster)
    {
        if (dynamic_cast<CmonsterWorld*>(*m_viMonster)->getMonsterFSM()->getstate() == STATE_TYPE::BATTLE)
        {
            m_playerM->getMario()->setSceneNum(0b0000);
            m_playerM->getMario()->setBeforeSceneNum(0b0010);
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
                (*m_viMonster)->getX() + 150,
                (*m_viMonster)->getY() + 50,
                m_playerM->getMario()->getSceneNum(),
                m_playerM->getMario()->getBeforeSceneNum(),
                m_playerM->getMario()->getisFight());
            m_monsterM->vecClear();
            SCENE->changeBattleScene("��Ʋ��");
            return;
        }
    }

    if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_door))
    {
        m_playerM->getMario()->setSceneNum(0b0000);
        m_playerM->getMario()->setBeforeSceneNum(0b0010);
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
            m_playerM->getMario()->getX(),
            m_playerM->getMario()->getY(),
            m_playerM->getMario()->getSceneNum(),
            m_playerM->getMario()->getBeforeSceneNum(),
            m_playerM->getMario()->getisFight());
        m_monsterM->vecClear();
        SCENE->changeScene("����");
    }
}

