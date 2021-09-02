#include "framework.h"
#include "CsceneBanditsWay.h"

CsceneBanditsWay::CsceneBanditsWay()
    :m_camera(new Ccamera), m_banditsWay(new CbanditsWay), m_playerM(new CplayerManager), m_door(RectMake(0, 0, 0, 0)), m_monsterM(new CmonsterManager)
{
}

CsceneBanditsWay::~CsceneBanditsWay()
{
    SAFE_DELETE(m_banditsWay);
    SAFE_DELETE(m_playerM);
    SAFE_DELETE(m_camera);
    SAFE_DELETE(m_monsterM);
}

HRESULT CsceneBanditsWay::init()
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
    m_playerM->getMario()->setX(PLAYERDATA->getX());
    m_playerM->getMario()->setY(PLAYERDATA->getY());
    m_playerM->getMario()->setSceneNum(PLAYERDATA->getSceneNum());
    m_door = RectMake(WINSIZEX / 2 + 80, WINSIZEY + 30, 50, 50);

    m_monsterM->addMonster(CHARACTER_TYPE::GOOMBA);
    m_monsterM->init();
    return S_OK;
}

void CsceneBanditsWay::release()
{
}

void CsceneBanditsWay::update()
{
    m_camera->update();
    m_camera->setTargetPoint(PointMake(m_playerM->getMarioRect()->left, m_playerM->getMarioRect()->top));
    m_banditsWay->update();
    m_playerM->update();
    m_monsterM->update();

    scenechange();
}

void CsceneBanditsWay::render()
{
    this->getMapBuffer()->render(getMemDC(), 0, 0, m_camera->getCameraPoint().x, m_camera->getCameraPoint().y, m_camera->getCameraWidth(), m_camera->getCameraHeight());

    m_camera->render();
    m_banditsWay->render();
    m_playerM->render();
    m_monsterM->render();

    //Rectangle(getMapDC(), m_door.left, m_door.top, m_door.right, m_door.bottom);
    //if (InputManager->isToggleKey(VK_TAB)) ZORDER->zorderRender(IMAGE->findImage("���������ȼ�"), ZDEBUG, 0, 0, 0);

    ZORDER->zorderTotalRender(getMapDC());
}

void CsceneBanditsWay::scenechange()
{
    RECT temp;
    if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_door))
    {
        m_playerM->getMario()->setSceneNum(0b0010);
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
            m_playerM->getMario()->getSceneNum());
        SCENE->changeScene("����");
    }
}
