#include "framework.h"
#include "CsceneTown.h"
CsceneTown::CsceneTown()
	:m_camera(new Ccamera), m_town(new Ctown), m_playerM(new CplayerManager), m_door(RectMake(0, 0, 0, 0))
{
}

CsceneTown::~CsceneTown()
{
    SAFE_DELETE(m_camera);
    SAFE_DELETE(m_town);
    SAFE_DELETE(m_playerM);
}

HRESULT CsceneTown::init()
{
	m_town->setCameraMemory(m_camera);
	m_playerM->init();
	m_door = RectMake(10, WINSIZEY + 230, 50, 50);
	return S_OK;
}

void CsceneTown::release()
{
	
}

void CsceneTown::update()
{
	m_camera->update();
	m_camera->setTargetPoint(PointMake(m_playerM->getMarioRect()->left, m_playerM->getMarioRect()->top));
	m_town->update();
	m_playerM->update();

    pixelCollision();
	scenechange();
}

void CsceneTown::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0, m_camera->getCameraPoint().x, m_camera->getCameraPoint().y, m_camera->getCameraWidth(), m_camera->getCameraHeight());

	m_camera->render();
	m_town->render();
	m_playerM->render();

	Rectangle(getMapDC(), m_door.left, m_door.top, m_door.right, m_door.bottom);
	if (InputManager->isToggleKey(VK_TAB)) IMAGE->findImage("¸¶À»¸ÊÇÈ¼¿")->render(getMapDC());
}

void CsceneTown::scenechange()
{
	RECT temp;
	if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_door))
	{
		SCENE->changeScene("¸¶¸®¿ÀÀÇÁý");
	}
}

void CsceneTown::pixelCollision()
{
    for (int i = m_playerM->getMario()->getY() - 1; i > m_playerM->getMario()->getY() - 5; i--)
    {
        COLORREF  color = GetPixel(IMAGE->findImage("¸¶À»¸ÊÇÈ¼¿")->getMemDC(), m_playerM->getMario()->getX(), i);

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
        COLORREF  color = GetPixel(IMAGE->findImage("¸¶À»¸ÊÇÈ¼¿")->getMemDC(), m_playerM->getMario()->getX(), i);

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
        COLORREF  color = GetPixel(IMAGE->findImage("¸¶À»¸ÊÇÈ¼¿")->getMemDC(), i, m_playerM->getMario()->getY());

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
        COLORREF  color = GetPixel(IMAGE->findImage("¸¶À»¸ÊÇÈ¼¿")->getMemDC(), i, m_playerM->getMario()->getY());

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            m_playerM->getMario()->setX(m_playerM->getMario()->getX() - m_playerM->getMario()->getSpeed());
        }
    }
}
