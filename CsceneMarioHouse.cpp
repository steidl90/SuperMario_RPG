#include "framework.h"
#include "CsceneMarioHouse.h"

CsceneMarioHouse::CsceneMarioHouse()
    :m_camera(new Ccamera), m_house(new Chouse), m_playerM(new CplayerManager), m_door(RectMake(0, 0, 0, 0))
{
}

CsceneMarioHouse::~CsceneMarioHouse()
{
    SAFE_DELETE(m_house);
    SAFE_DELETE(m_playerM);
    SAFE_DELETE(m_camera);
}

HRESULT CsceneMarioHouse::init()
{
    m_playerM->init();
    m_door = RectMake(WINSIZEX / 2 + 80, WINSIZEY + 30, 50, 50);
    return S_OK;
}

void CsceneMarioHouse::release()
{
    
}

void CsceneMarioHouse::update()
{
    m_camera->update();
    m_camera->setTargetPoint(PointMake(m_playerM->getMarioRect()->left, m_playerM->getMarioRect()->top));
    m_house->update();
    m_playerM->update();

    pixelCollision();
    scenechange();
}

void CsceneMarioHouse::render()
{
    this->getMapBuffer()->render(getMemDC(), 0, 0, m_camera->getCameraPoint().x, m_camera->getCameraPoint().y, m_camera->getCameraWidth(), m_camera->getCameraHeight());

    m_camera->render();
    m_house->render();
    m_playerM->render();

    Rectangle(getMapDC(), m_door.left, m_door.top, m_door.right, m_door.bottom);
}

void CsceneMarioHouse::scenechange()
{
    RECT temp;
    if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_door))
    {
        SCENE->changeScene("마을");
    }
}

void CsceneMarioHouse::pixelCollision()
{
    for (int i = m_playerM->getMario()->getY() - 1; i > m_playerM->getMario()->getY() - 5; i--)
    {
        COLORREF  color = GetPixel(IMAGE->findImage("마리오집픽셀")->getMemDC(), m_playerM->getMario()->getX(), i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            m_playerM->getMario()->setY(m_playerM->getMario()->getY() + m_playerM->getMario()->getSpeed());
        }
    }

    for (int i = m_playerM->getMario()->getY() + 5; i < m_playerM->getMario()->getY() + 50; i++)
    {
        COLORREF  color = GetPixel(IMAGE->findImage("마리오집픽셀")->getMemDC(), m_playerM->getMario()->getX(), i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            m_playerM->getMario()->setY(m_playerM->getMario()->getY() - m_playerM->getMario()->getSpeed());
        }
    }

    for (int i = m_playerM->getMario()->getX() - 1; i > m_playerM->getMario()->getX() - 10; i--)
    {
        COLORREF  color = GetPixel(IMAGE->findImage("마리오집픽셀")->getMemDC(), i, m_playerM->getMario()->getY());

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            m_playerM->getMario()->setX(m_playerM->getMario()->getX() + m_playerM->getMario()->getSpeed());
        }
    }

    for (int i = m_playerM->getMario()->getX() + 1; i < m_playerM->getMario()->getX() + 10; i++)
    {
        COLORREF  color = GetPixel(IMAGE->findImage("마리오집픽셀")->getMemDC(), i, m_playerM->getMario()->getY());

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            m_playerM->getMario()->setX(m_playerM->getMario()->getX() - m_playerM->getMario()->getSpeed());
        }
    }
}
