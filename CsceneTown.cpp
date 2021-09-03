#include "framework.h"
#include "CsceneTown.h"
CsceneTown::CsceneTown()
	:m_town(new Ctown), m_playerM(new CplayerManager), m_doorA(RectMake(0, 0, 0, 0)), m_doorB(RectMake(0, 0, 0, 0))
{
}

CsceneTown::~CsceneTown()
{
    SAFE_DELETE(m_town);
    SAFE_DELETE(m_playerM);
}

HRESULT CsceneTown::init()
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
	m_playerM->getMario()->setSceneNum(PLAYERDATA->getSceneNum());
	m_playerM->getMario()->setBeforeSceneNum(PLAYERDATA->getBeforeSceneNum());

	if (m_playerM->getMario()->getBeforeSceneNum() == 0b0001)
	{
		m_playerM->getMario()->setX(80);
		m_playerM->getMario()->setY(MAPSIZEY - 470);
	}
	else if (m_playerM->getMario()->getBeforeSceneNum() == 0b0010)
	{
		m_playerM->getMario()->setX(MAPSIZEX - 210);
		m_playerM->getMario()->setY(WINSIZEY + 530);
	}

	m_doorA = RectMake(10, WINSIZEY + 230, 50, 50);
	m_doorB = RectMake(MAPSIZEX - 180, WINSIZEY + 550, 50, 50);
	return S_OK;
}

void CsceneTown::release()
{
}

void CsceneTown::update()
{
	CAMERA->update();
	CAMERA->setTargetPoint(PointMake(m_playerM->getMarioRect()->left, m_playerM->getMarioRect()->top));
	m_town->update();
	m_playerM->update();

	scenechange();
}

void CsceneTown::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0, CAMERA->getCameraPoint().x, CAMERA->getCameraPoint().y, CAMERA->getCameraWidth(), CAMERA->getCameraHeight());

	m_town->render();
	m_playerM->render();

	if (InputManager->isToggleKey(VK_TAB))
	{
		ZORDER->zorderRender(IMAGE->findImage("¸¶À»¸ÊÇÈ¼¿"), ZDEBUG, 0, 0, 0);
		Rectangle(getMapDC(), m_doorA.left, m_doorA.top, m_doorA.right, m_doorA.bottom);
	}
	ZORDER->zorderTotalRender(getMapDC());
}

void CsceneTown::scenechange()
{
	RECT temp;
	if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_doorA))
	{
		m_playerM->getMario()->setSceneNum(0b0001);
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
			m_playerM->getMario()->getBeforeSceneNum());
		SCENE->changeScene("¸¶¸®¿ÀÀÇÁý");
	}

	if (IntersectRect(&temp, m_playerM->getMarioRect(), &m_doorB))
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
			m_playerM->getMario()->getSceneNum(),
			m_playerM->getMario()->getBeforeSceneNum());
		SCENE->changeScene("µµµÏ·Îµå");
	}
}

