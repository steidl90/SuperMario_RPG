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

	scenechange();
}

void CsceneTown::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0, m_camera->getCameraPoint().x, m_camera->getCameraPoint().y, m_camera->getCameraWidth(), m_camera->getCameraHeight());

	m_camera->render();
	m_town->render();
	m_playerM->render();

	if (InputManager->isToggleKey(VK_TAB))
	{
		IMAGE->findImage("마을맵픽셀")->render(getMapDC());
		Rectangle(getMapDC(), m_door.left, m_door.top, m_door.right, m_door.bottom);
	}

    /*TCHAR str[10000];
    sprintf_s(str, "%.1f /////// %.1f", m_playerM->getMario()->getX(), m_playerM->getMario()->getY());
    TextOut(getMemDC(), 100, 100, str, strlen(str));*/

}

void CsceneTown::scenechange()
{
	RECT temp;
	if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_door))
	{
		m_playerM->getMario()->setSceneNum(0b0001);
		SCENE->changeScene("마리오의집");
	}
}

