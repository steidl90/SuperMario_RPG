#pragma once
#include "Cunit.h"
#include "Cplayer.h"
#include "CplayerAttack.h"
#include "camera.h"
#include "CplayerUi.h"
#include "CinventoryUi.h"
#include "CdropItem.h"
#include "Cquest.h"

class CaStar;
class CenemyManager;
class Cmevius;
class CplayerManager :public Cunit
{
private:
	camera* m_camera;
	Cplayer* m_player;
	CplayerUi* m_playerUi;
	CinventoryUi* m_InventoryUI;
	Cinventory* m_inventory;
	CenemyManager* m_enemy;
	Cmevius* m_boss;
	CdropItem* m_dropItem;
	Cquest* m_quest;
	int m_deathCount;
private:
	
	//list<POINT>* m_fastLoadLocation;

	bool isInventoryOn;

	int m_timer;

	bool isAstar;
public:
	CplayerManager();
	~CplayerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	RECT* getplayerRect() { return m_player->getplayerMoveRC(); }

	Cplayer* getPlayer() { return m_player; }

	//void setFastLoadLocation(list<POINT>* lp) { m_fastLoadLocation = lp; }

	Cinventory* getInventoryMemory() { return m_inventory; }

	void showPlayerStat();

	// Ãß°¡
	void setEnemyMemory(CenemyManager* enemy) { m_enemy = enemy; }
	void setBossMemory(Cmevius* boss) { m_boss = boss; }
	void setQuestMemory(Cquest* quest) { m_quest = quest; }

	void collisionEnemy();
	void getItem();

	void setCheckTile(tagTile* tile) { m_player->setCheckTile(tile); }
	void setTileAttribute(ATTRIBUTE* att) { m_player->setAttribute(att); }

	CdropItem* getDropItem() { return m_dropItem; }

	void usePotion();
};