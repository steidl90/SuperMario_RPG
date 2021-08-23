#include "framework.h"
#include "CsceneTown.h"

CsceneTown::CsceneTown() :m_timerHp(NULL), m_timerMp(NULL)
{
}

CsceneTown::~CsceneTown()
{
}

HRESULT CsceneTown::init()
{
	m_wingImage = IMAGE->findImage("풍차날개");
	ANIMATION->addDefAnimation("풍차", "풍차날개", 10, false, true);
	m_wingAni = ANIMATION->findAnimation("풍차");

	ANIMATION->start("풍차");

	m_wingX[0] = 575;
	m_wingY[0] = 200;

	m_camera = new camera;
	m_camera->init();

	m_town = new Ctown;
	m_town->setCameraMemory(m_camera);
	m_town->init();

	m_player = new CplayerManager;
	m_player->init();
	m_player->setCheckTile(m_town->getMap());
	m_player->setTileAttribute(m_town->getAttribute());

	m_player->getPlayer()->setAtk(DATA->getAtk());
	m_player->getPlayer()->setCritical(DATA->getCritical());
	m_player->getPlayer()->setCriticalAtk(DATA->getCriticalAtk());
	m_player->getPlayer()->setDef(DATA->getDef());
	m_player->getPlayer()->setExp(DATA->getExp());
	m_player->getPlayer()->setGold(DATA->getGold());	
	m_player->getPlayer()->setHp(DATA->getHp());
	m_player->getPlayer()->setMaxHp(DATA->getMaxHp());
	m_player->getPlayer()->setMp(DATA->getMp());
	m_player->getPlayer()->setMaxMp(DATA->getMaxMp());
	m_player->getPlayer()->setLv(DATA->getLv());
	m_player->getPlayer()->setSpeed(DATA->getSpeed());
	m_player->getPlayer()->setPlayerX(DATA->getX());
	m_player->getPlayer()->setPlayerY(DATA->getY());

	m_player->getInventoryMemory()->setEquipItem(DATA->getEquipItem());
	m_player->getInventoryMemory()->setvWeaponList(DATA->getvWeaponList());
	m_player->getInventoryMemory()->setvArmorList(DATA->getvArmorList());
	m_player->getInventoryMemory()->setvShoesList(DATA->getvShoesList());
	m_player->getInventoryMemory()->setvGlovesList(DATA->getvGlovesList());
	m_player->getInventoryMemory()->setvPendantList(DATA->getvPendantList());

	//m_aStar = new CaStar;
	//m_aStar->setCameraMemory(m_camera);
	//m_aStar->setAttribute(m_town->getAttribute());
	//m_aStar->init();

	m_shop = new Cshop;
	m_shop->setInventoryMemory(m_player->getInventoryMemory());
	m_shop->setPlayerMemory(m_player->getPlayer());
	m_shop->init();
	

	m_shopUi = new CshopUi;
	//m_shopUi->setInventoryMemory(m_player->getInventoryMemory());
	//m_shopUi->setPlayerMemory(m_player->getPlayer());
	m_shopUi->setShopMemory(m_shop);
	m_shopUi->init();

	m_changeRect = RectMake(MAPSIZE - 10, MAPSIZE * 0.25 + 120, 100, 100);

	m_shopRect = RectMake(310, 230, IMAGE->findImage("NPC에릭")->getFrameWidth() * 2, IMAGE->findImage("NPC에릭")->getFrameHeight() * 2);
	m_npcRect = RectMake(WINSIZEX/2 , WINSIZEY/2, 100, 100);

	m_npc = new CNPC;
	m_npc->init();

	m_quest = new Cquest;
	m_quest->init();
	m_quest->setPlayer(m_player->getPlayer());
	m_quest->setNPC(m_npc);

	m_player->setQuestMemory(m_quest);

	//TODO::수정이 필요함 겟-셋-겟

	m_quest->setQuest(DATA->getQuest());
	m_quest->setMaxQuest(DATA->getMaxQuest());
	m_quest->setIsDialog(DATA->getIsDialog());
	m_quest->setIsQuesting(DATA->getIsQuesting());
	m_quest->setIsComplete(DATA->getIsComplete());
	
	isShopOn = false;
	isNpcCollison = false;

	////////////////////////////
	m_buttonImage = IMAGE->findImage("버튼");

	m_x = m_player->getplayerRect()->left + 15;
	m_y = m_player->getplayerRect()->top;

	return S_OK;
}

void CsceneTown::release()
{
	SAFE_DELETE(m_camera);
	SAFE_DELETE(m_town);
	SAFE_DELETE(m_player);
	//SAFE_DELETE(m_aStar);
	SAFE_DELETE(m_shop);
	SAFE_DELETE(m_shopUi);
	SAFE_DELETE(m_npc);
}

void CsceneTown::update()
{
	m_camera->update();
	m_camera->setTargetPoint(PointMake(m_player->getplayerRect()->left, m_player->getplayerRect()->top));
	m_town->update();
	m_quest->update();
	m_player->update();

	//NPC
	m_npc->update();

	if (isShopOn) m_shopUi->update();

	shopOn();


	//체력 리젠
	if (m_player->getPlayer()->getHp() < m_player->getPlayer()->getMaxHp())
	{
		if (m_timerHp + 3 < TIME->getWorldTime())
		{
			m_player->getPlayer()->setHp(m_player->getPlayer()->getHp() + 10);
			m_timerHp = TIME->getWorldTime();
		}
	}
	else if (m_player->getPlayer()->getHp() > m_player->getPlayer()->getMaxHp())
	{
		m_player->getPlayer()->setHp(m_player->getPlayer()->getMaxHp());
	}

	//마나 리젠
	if (m_player->getPlayer()->getMp() < m_player->getPlayer()->getMaxMp())
	{
		if (m_timerMp + 3 < TIME->getWorldTime())
		{
			m_player->getPlayer()->setMp(m_player->getPlayer()->getMp() + 5);
			m_timerMp = TIME->getWorldTime();
		}
	}
	else if (m_player->getPlayer()->getMp() > m_player->getPlayer()->getMaxMp())
	{
		m_player->getPlayer()->setMp(m_player->getPlayer()->getMaxMp());
	}

	m_buttonRc = RectMake(m_x, m_y, m_buttonImage->getFrameWidth(), m_buttonImage->getFrameHeight());
	m_x = m_player->getplayerRect()->left + 5;
	m_y = m_player->getplayerRect()->top - 30;

	sceneChange();
	m_wingRect = RectMakeCenter(m_wingX[0], m_wingY[0], m_wingImage->getFrameWidth(), m_wingImage->getFrameHeight());

}

void CsceneTown::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0, m_camera->getCameraPoint().x, m_camera->getCameraPoint().y, m_camera->getCameraWidth(), m_camera->getCameraHeight());
	this->getMapBuffer()->mapRender(getMemDC(), WINSIZEX - IMAGE->findImage("MiniMapUi")->getWidth(), 70);

	m_camera->render();
	m_town->render();
	//NPC
	m_npc->render();
	m_quest->render();
	m_player->render();

	if (isShopOn) m_shopUi->render();
	else this->shopCollision();

	m_wingImage->aniRender(getMapDC(), m_wingX[0]-10, m_wingY[0]-10, m_wingAni);
	TCHAR str[256];
	sprintf_s(str, "이노야 마을");
	TextOut(getMemDC(), WINSIZEX - 165, 20, str, strlen(str));

	npcCollison();

}

void CsceneTown::sceneChange()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerRect(), &m_changeRect))
	{
		DATA->setData(m_player->getPlayer()->getAtk(),
			m_player->getPlayer()->getDef(),
			m_player->getPlayer()->getHp(),
			m_player->getPlayer()->getMaxHp(),
			m_player->getPlayer()->getMp(),
			m_player->getPlayer()->getMaxMp(),
			m_player->getPlayer()->getCritical(),
			m_player->getPlayer()->getLv(),
			m_player->getPlayer()->getExp(),
			m_player->getPlayer()->getGold(),
			m_player->getPlayer()->getCriticalAtk(),
			m_player->getPlayer()->getSpeed(),
			m_player->getPlayer()->getPlayerX(),
			m_player->getPlayer()->getPlayerY());
		DATA->setEquipItem(m_player->getInventoryMemory()->getEquipItem());
		DATA->setvWeaponList(m_player->getInventoryMemory()->getvWeaponList());
		DATA->setvArmorList(m_player->getInventoryMemory()->getvArmorList());
		DATA->setvShoesList(m_player->getInventoryMemory()->getvShoesList());
		DATA->setvGlovesList(m_player->getInventoryMemory()->getvGlovesList());
		DATA->setvPendantList(m_player->getInventoryMemory()->getvPendantList());

		DATA->setQuest(m_quest->getQuest());
		DATA->setMaxQuest(m_quest->getMaxQuest());
		DATA->setIsDialog(m_quest->getIsDialog());
		DATA->setIsQuesting(m_quest->getIsQuesting());
		DATA->setIsComplete(m_quest->getIsComplete());

		SCENE->changeScene("던전");
	}
}

void CsceneTown::shopOn()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerRect(), &m_shopRect))
	{
		if (InputManager->isOnceKeyDown('P'))
		{
			isShopOn = !isShopOn;
		}
	}
	else
	{
		isShopOn = false;
	}
	//isShopOn = true;

	if (m_shopUi->getExit())
	{
		isShopOn = false;
		m_shopUi->setExit(false);
	}
}

void CsceneTown::npcCollison()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerRect(), m_npc->getKaylaRect()))
	{
		m_buttonImage->render(getMapDC(), m_x, m_y);
		TCHAR str[256];
		sprintf_s(str, "회복하기");
		SetBkMode(getMapDC(), TRANSPARENT);
		SetTextColor(getMapDC(), RGB(255, 255, 255));
		TextOut(getMapDC(), m_x - 20, m_y + 20, str, strlen(str));
		TCHAR buttonstr[256];
		sprintf_s(buttonstr, "F");
		TextOut(getMapDC(), m_x + 10, m_y + 5, buttonstr, strlen(buttonstr));
	}

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	if (InputManager->isOnceKeyDown('F'))
	{
		RECT dest;
		if (IntersectRect(&dest, m_player->getplayerRect(), m_npc->getKaylaRect()))
		{
			isNpcCollison = !isNpcCollison;
			//체력 회복
			if (m_player->getPlayer()->getHp() < m_player->getPlayer()->getMaxHp())
			{
				if (m_timerHp + 0.5 < TIME->getWorldTime())
				{
					m_player->getPlayer()->setHp(m_player->getPlayer()->getMaxHp());
					m_timerHp = TIME->getWorldTime();
				}
			}

			//마나 회복
			if (m_player->getPlayer()->getMp() < m_player->getPlayer()->getMaxMp())
			{
				if (m_timerMp + 0.5 < TIME->getWorldTime())
				{
					m_player->getPlayer()->setMp(m_player->getPlayer() -> getMaxMp());
					m_timerMp = TIME->getWorldTime();
				}
			}

		}
	}
}

void CsceneTown::shopCollision()
{
	RECT temp;
	if (IntersectRect(&temp, m_player->getplayerRect(), &m_shopRect))
	{
		m_buttonImage->render(getMemDC(), m_x, m_y);
		TCHAR str[256];
		sprintf_s(str, "상점방문");
		TextOut(getMemDC(), m_x - 20, m_y + 20, str, strlen(str));
		TCHAR buttonstr[256];
		sprintf_s(buttonstr, "P");
		TextOut(getMemDC(), m_x + 10, m_y + 5, buttonstr, strlen(buttonstr));
	}


}