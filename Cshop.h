#pragma once
#include"Citem.h"
#include"Cinventory.h"
// 오류나면 전방참조

class Cplayer;
class Cshop
{
private:
	Cplayer* m_player;
	Cinventory* m_myInventory;
private:

	vector<Citem*> m_vTotalList;

	SelectItem m_selectItem;

	Citem* m_shopSelectItem;

	Potion m_potion;

public:

	HRESULT init();
	void release();
	void update();
	//void render();

	vector<Citem*>* getTotalList() { return &m_vTotalList; }

	Citem* getShopSelectItem() { return m_shopSelectItem; }
	SelectItem* getSelectItem() { return &m_selectItem; }

	void setShopSelectItem(Citem* item) { m_shopSelectItem = item; }


	void buyItem(Citem* item);
	void sellItem();

	void setPlayerMemory(Cplayer* p) { m_player = p; }
	void setInventoryMemory(Cinventory* inven) { m_myInventory = inven; }

	Cplayer* getPlayer() {	return m_player; };
	Cinventory* getInventory() { return m_myInventory; };
};

