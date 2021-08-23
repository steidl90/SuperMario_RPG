#pragma once
#include"gameNode.h"
#include"Cshop.h"
// 오류나면 전방참조
class Cplayer;
class CshopUi : public gameNode
{
private:
	//Cinventory* m_myInventory;
	Cshop* m_shop;
private:
	
	// 인벤토리 파트
	RECT m_inventoryRect;
	int m_inventoryUiX;
	int m_inventoryUiY;
	vector<RECT> m_vItemListRect;
	int m_itemListX;
	int m_itemListY;
	RECT m_ItemInfoRect;
	int m_itemInfoX;
	int m_itemInfoY;
	RECT m_sellButton;
	int m_inventoryButtonX;
	int m_inventoryButtonY;
	//Citem* m_selectItem;

	// 상점 파트
	RECT m_shopRect;
	int m_shopUiX;
	int m_shopUiY;
	vector<RECT> m_vShopListRect;
	int m_shopListX;
	int m_shopListY;
	RECT m_buyButton;
	int m_shopButtonX;
	int m_shopButtonY;
	//Citem* m_selectShopItem;
	RECT m_shopInfo;
	int m_shopInfoX;
	int m_shopInfoY;
	RECT m_exitButton;

	// 기능 구현
	ITEMTYPE m_selectType;
	int m_showIndex;
	int m_showEndIndex;
	int m_selectRenderX;
	int m_selectRenderY;

	bool isButtonClick;
	bool isKeyUp;

	bool isSelectRender;
	// 상점부분
	bool isSelectShop;
	//int m_selectShopX; 이미지없음 보류
	//int m_selectShopY;

	bool m_exit;

public:

	HRESULT init();
	void release();
	void update();
	void render();
	// 클래스 메모리 set

	bool getExit() { return m_exit; }
	void setExit(bool b) { m_exit = b; }
	//void setInventoryMemory(Cinventory* inven) { m_myInventory = inven; }
	void setShopMemory(Cshop* shop) { m_shop = shop; }

	void showItemType();
	void showInvenItemList(vector<Citem*>* item);
	void showItemInfo();

	void itemStatInfo();

	void setShowIndex();


	void selectItem();
	void showEquipSelect();

	// 상점
	void sellItem();
	void buyItem();
	void exitShop();

	void showShopItemList(vector<Citem*>* item);
	void selectShopItem();

	void showShopInfo();
	void shopItemStatInfo();
};

