#pragma once
#include"gameNode.h"
#include"Cinventory.h"
// �κ��丮 include �������� ��������

class Cplayer;
class CinventoryUi : public gameNode
{
private:
	Cinventory* m_Inventory;
	Cplayer* m_player;

private:

	// �⺻ UI �������
	RECT m_InventoryRect;
	int m_uiX;
	int m_uiY;
	int m_itemListX;
	int m_itemListY;
	int m_EquipItemX;
	int m_EquipItemY;
	int m_itemInfoX;
	int m_itemInfoY;
	int m_functionButtonX;
	int m_functionButtonY;

	vector<RECT> m_vItemListRect;
	vector<RECT> m_vEquipItemSubRect;
	vector<RECT> m_vEquipItemMainRect;
	RECT m_ItemInfoRect;

	RECT m_equipButton;
	RECT m_abandonButton;

	// ��ư Ŭ���� stay�ٿ��� onceó�� ��������..
	bool isButtonClick;
	bool isKeyUp;

	// ��� ���� �������
	ITEMTYPE m_selectType;
	//Citem* m_selectItem;
	Citem m_itemInit[5];
	// ���� ����
	EquipItem m_equipItem[5];

	int m_showIndex;
	int m_showEndIndex;
	int m_selectRenderX;
	int m_selectRenderY;
	int m_equipRenderX;
	int m_equipRenderY;
	int m_clickCount;

	bool isSelectRender;
	int m_SelectIndex;
	int m_compareTime;

	RECT m_clickCheckRect;

	POINT m_equipRenderPoint[5];  // �ʿ���� �����ε� �̰� ���ָ� ������ ����... ???

public:

	CinventoryUi();
	~CinventoryUi();

	HRESULT init();
	void release();
	void update();
	void render();

	// �κ��丮 ���� set
	void setInventoryMemory(Cinventory* inven) { m_Inventory = inven; }
	// �÷��̾� ���� set
	void setPlayerMemory(Cplayer* player) { m_player = player; }

	// Ÿ���� ���������� ������ ����Ʈ�� showIndex (������ �ε��� ����) ����
	void setShowIndex();

	// Ÿ�Ժ� ������ ���
	void showListItemType();
	void showItemList(vector<Citem*>* list);

	// ���� �׵θ� ���
	void showEquipSelect();

	// ����Ʈ���� ���ý� ���� / + ����
	void selectItem();
	void selectEquipItem();

	// ������ ���� ����!
	void setPlayerStat(int index);
	void clickEquipButton();
	// ���â rect Ŭ���� ���� ������ Ÿ�� ����
	void selectItemTypeMain();
	void selectItemTypeSub();

	// ������ ������ â
	void showItemInfo();
	void showItemCompare();

	// ������ ������ ����
	void abandonItem();

	// ������ ���� ����
	void unEquipItem();
	
	// ���� ����
	void selectPotion();
	void showPotionInfo();
};

