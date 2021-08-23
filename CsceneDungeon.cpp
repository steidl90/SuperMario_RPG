#include "framework.h"
#include "CsceneDungeon.h"
#include "Celemental.h"
#include "Cmonk.h"
#include "Cpriest.h"
#include "Cprison.h"
#include "Cslime.h"
CsceneDungeon::CsceneDungeon()
{
}

CsceneDungeon::~CsceneDungeon()
{
}

HRESULT CsceneDungeon::init()
{
	m_camera = new camera;
	m_camera->init();

	m_dungeon = new Cdungeon;
	m_dungeon->init();
	m_dungeon->setCameraMemory(m_camera);

	m_player = new CplayerManager;
	m_player->init();
	m_player->setCheckTile(m_dungeon->getMap());
	m_player->setTileAttribute(m_dungeon->getAttribute());

	m_boss = new Cmevius;
	m_boss->init(PointMake(WINSIZEX / 2, -50), 30000, 50);
	m_boss->setPlayer(m_player->getPlayer());
	m_boss->setDropItem(m_player->getDropItem());

	m_enemyManager = new CenemyManager;
	m_enemyManager->init();
	m_enemyManager->setPlayer(m_player->getPlayer());

	m_player->setEnemyMemory(m_enemyManager);
	m_player->setBossMemory(m_boss);

	m_player->getPlayer()->setAtk(DATA->getAtk());
	m_player->getPlayer()->setCritical(DATA->getCritical());
	m_player->getPlayer()->setCriticalAtk(DATA->getCriticalAtk());
	m_player->getPlayer()->setDef(DATA->getDef());
	m_player->getPlayer()->setExp(DATA->getExp());
	m_player->getPlayer()->setGold(DATA->getGold());
	m_player->getPlayer()->setHp(DATA->getHp());
	m_player->getPlayer()->setMaxHp(DATA->getMaxHp());
	m_player->getPlayer()->setLv(DATA->getLv());
	m_player->getPlayer()->setMp(DATA->getMp());
	m_player->getPlayer()->setMaxMp(DATA->getMaxMp());
	m_player->getPlayer()->setSpeed(DATA->getSpeed());
	m_player->getPlayer()->setPlayerX(200);
	m_player->getPlayer()->setPlayerY(MAPSIZE - 300);

	m_player->getInventoryMemory()->setEquipItem(DATA->getEquipItem());
	m_player->getInventoryMemory()->setvWeaponList(DATA->getvWeaponList());
	m_player->getInventoryMemory()->setvArmorList(DATA->getvArmorList());
	m_player->getInventoryMemory()->setvShoesList(DATA->getvShoesList());
	m_player->getInventoryMemory()->setvGlovesList(DATA->getvGlovesList());
	m_player->getInventoryMemory()->setvPendantList(DATA->getvPendantList());

	m_changeRect = RectMake(170, MAPSIZE - 230, 100, 50);

	m_quest = new Cquest;


	m_quest->setQuest(DATA->getQuest());
	m_quest->setMaxQuest(DATA->getMaxQuest());
	m_quest->setIsDialog(DATA->getIsDialog());
	m_quest->setIsQuesting(DATA->getIsQuesting());
	m_quest->setIsComplete(DATA->getIsComplete());
	m_player->setQuestMemory(m_quest);


	int exp = 20;

	//슬라임 설정 = 전역에 골고루
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Cslime* m_slime = new Cslime;
			m_slime->setPlayer(m_player->getPlayer());
			m_slime->setAttribute(m_dungeon->getAttribute());
			m_slime->init(PointMake(RND->getFromIntTo(800, 1000) + i * RND->getFromIntTo(130, 180),
				RND->getFromIntTo(250, 350) + j * RND->getFromIntTo(100, 150)),
				900, 1, 1, exp, 500);
			m_enemyManager->registerEnemy(m_slime);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Cslime* m_slime2 = new Cslime;
			m_slime2->setPlayer(m_player->getPlayer());
			m_slime2->setAttribute(m_dungeon->getAttribute());
			m_slime2->init(PointMake(RND->getFromIntTo(100, 150) + i * RND->getFromIntTo(100, 180),
				RND->getFromIntTo(600, 650) + j * RND->getFromIntTo(120, 150)),
				900, 1, 1, exp, 500);
			m_enemyManager->registerEnemy(m_slime2);
		}
	}
	//엘리멘탈 설정 = 좌측 위, 중앙
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Celemental* m_elemental = new Celemental;
			m_elemental->setPlayer(m_player->getPlayer());
			m_elemental->setAttribute(m_dungeon->getAttribute());
			m_elemental->init(PointMake(RND->getFromIntTo(100, 150) + i * RND->getFromIntTo(120, 150),
				270 + j * RND->getFromIntTo(50, 70)),
				500, 10,2, exp, 500);
			m_enemyManager->registerEnemy(m_elemental);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			Celemental* m_elemental2 = new Celemental;
			m_elemental2->setPlayer(m_player->getPlayer());
			m_elemental2->setAttribute(m_dungeon->getAttribute());
			m_elemental2->init(PointMake(RND->getFromIntTo(900, 1000) + i * RND->getFromIntTo(120, 150),
				RND->getFromIntTo(250, 350) + j * RND->getFromIntTo(100, 150)),
				500, 10,2, exp, 500);
			m_enemyManager->registerEnemy(m_elemental2);
		}
	}
	//몽크 설정 = 좌측 중간
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Cmonk* m_monk = new Cmonk;
			m_monk->setPlayer(m_player->getPlayer());
			m_monk->setAttribute(m_dungeon->getAttribute());
			m_monk->init(PointMake(RND->getFromIntTo(100, 150) + i * RND->getFromIntTo(100, 180),
				RND->getFromIntTo(600, 650) + j * RND->getFromIntTo(120, 150)),
				700, 20, 3, exp, 350);
			m_enemyManager->registerEnemy(m_monk);
		}
	}
	//프리스트 설정 = 중 상단, 좌 중단 1마리씩
	for (int i = 0; i <2 ; i++)
	{
		Cpriest* m_priest = new Cpriest;
		m_priest->setPlayer(m_player->getPlayer());
		m_priest->setAttribute(m_dungeon->getAttribute());
		m_priest->init(PointMake(900 + i * 650, 200 + i * 400),
			900, 50, 5, exp, 500);
		m_enemyManager->registerEnemy(m_priest);
	}
	//교도관 설정 = 중앙 하단
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Cprison* m_prison = new Cprison;
			m_prison->setPlayer(m_player->getPlayer());
			m_prison->setAttribute(m_dungeon->getAttribute());
			m_prison->init(PointMake(950 + i * 100, 1050 + j * 100),
				700, 40, 4, exp, 500);
			m_enemyManager->registerEnemy(m_prison);
		}
	}
	return S_OK;
}

void CsceneDungeon::release()
{
	SAFE_DELETE(m_camera);
	SAFE_DELETE(m_dungeon);
	SAFE_DELETE(m_player);
	SAFE_DELETE(m_enemyManager);
	SAFE_DELETE(m_boss);
	EFFECT->release();
}

void CsceneDungeon::update()
{
	m_camera->update();
	m_dungeon->update();
	m_player->update();
	m_enemyManager->update();
	m_enemyManager->collision();
	m_camera->setTargetPoint(PointMake(m_player->getplayerRect()->left, m_player->getplayerRect()->top));
	if (m_enemyManager->getEnemy()->size() == 0)
	{
		m_boss->update();
		m_boss->collision();
	}
	m_player->collisionEnemy();
	m_quest->update();
	sceneChange();
}

void CsceneDungeon::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0, m_camera->getCameraPoint().x, m_camera->getCameraPoint().y, m_camera->getCameraWidth(), m_camera->getCameraHeight());
	this->getMapBuffer()->mapRender(getMemDC(), WINSIZEX - IMAGE->findImage("MiniMapUi")->getWidth(), 70);

	m_camera->render();
	m_dungeon->render();
	m_enemyManager->render();
	m_boss->render();
	m_player->render();
	m_quest->render();
	//Rectangle(getMapDC(), m_changeRect.left, m_changeRect.top, m_changeRect.right, m_changeRect.bottom);

	TCHAR str[256];
	sprintf_s(str, "메비우스의 거처");
	TextOut(getMemDC(), WINSIZEX - 177, 20, str, strlen(str));
}

void CsceneDungeon::sceneChange()
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
			MAPSIZE - 50,
			WINSIZEY / 2 + 150);

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

		SCENE->changeScene("마을");
	}
	else if (m_player->getPlayer()->getHp() < 0)
	{
		m_player->getPlayer()->setHp(50);
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
			WINSIZEX - 400,
			WINSIZEY / 2 + 270);

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

		SCENE->changeScene("마을");
	}
}
