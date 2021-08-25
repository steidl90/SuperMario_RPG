#include "framework.h"
#include "CsceneTown.h"
CsceneTown::CsceneTown() :m_camera(new camera), m_town(new Ctown), m_player(new CplayerManager)
{
}

CsceneTown::~CsceneTown()
{
}

HRESULT CsceneTown::init()
{
	m_town->setCameraMemory(m_camera);
	m_player->init();
	return S_OK;
}

void CsceneTown::release()
{
	SAFE_DELETE(m_camera);
	SAFE_DELETE(m_town);
	SAFE_DELETE(m_player);
}

void CsceneTown::update()
{
	m_camera->update();
	m_camera->setTargetPoint(PointMake(m_player->getMarioRect()->left, m_player->getMarioRect()->top));
	m_town->update();
	m_player->update();
}

void CsceneTown::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0, m_camera->getCameraPoint().x, m_camera->getCameraPoint().y, m_camera->getCameraWidth(), m_camera->getCameraHeight());

	m_camera->render();
	m_town->render();
	m_player->render();
}