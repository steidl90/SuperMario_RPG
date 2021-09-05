#include "framework.h"
#include "CsceneMarioHouse.h"

CsceneMarioHouse::CsceneMarioHouse()
    : m_house(new Chouse), m_playerM(new CplayerManager), m_door(RectMake(0, 0, 0, 0))
{
}

CsceneMarioHouse::~CsceneMarioHouse()
{
    SAFE_DELETE(m_house);
    SAFE_DELETE(m_playerM);
}

HRESULT CsceneMarioHouse::init()
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
    m_playerM->getMario()->setX(500);
    m_playerM->getMario()->setY(500);
    m_playerM->getMario()->setSceneNum(PLAYERDATA->getSceneNum());
    m_playerM->getMario()->setisFight(PLAYERDATA->getisFight());
    m_door = RectMake(WINSIZEX / 2 + 80, WINSIZEY + 30, 50, 50);
    return S_OK;
}

void CsceneMarioHouse::release()
{
    
}

void CsceneMarioHouse::update()
{
    CAMERA->update();
    CAMERA->setTargetPoint(PointMake(m_playerM->getMarioRect()->left, m_playerM->getMarioRect()->top));
    m_house->update();
    m_playerM->update();

    scenechange();
}

void CsceneMarioHouse::render()
{
    this->getMapBuffer()->render(getMemDC(), 0, 0, CAMERA->getCameraPoint().x, CAMERA->getCameraPoint().y, CAMERA->getCameraWidth(), CAMERA->getCameraHeight());

    m_house->render();
    m_playerM->render();

    Rectangle(getMapDC(), m_door.left, m_door.top, m_door.right, m_door.bottom);
    if (InputManager->isToggleKey(VK_TAB)) ZORDER->zorderRender(IMAGE->findImage("마리오집픽셀"), ZDEBUG, 0, 0, 0);

    ZORDER->zorderTotalRender(getMapDC());
}

void CsceneMarioHouse::scenechange()
{
    RECT temp;
    if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_door))
    {
        m_playerM->getMario()->setSceneNum(0b0000);
        m_playerM->getMario()->setBeforeSceneNum(0b0001);
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
        SCENE->changeScene("마을");
    }
}