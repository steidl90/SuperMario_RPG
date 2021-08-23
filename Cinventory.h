#pragma once
#include"Citem.h"



class Cinventory
{
	vector<Citem*> m_vWeaponList;
	vector<Citem*> m_vArmorList;
	vector<Citem*> m_vShoesList;
	vector<Citem*> m_vGlovesList;
	vector<Citem*> m_vPendantList;

	// 기능 구현 멤버변수
	// 구조 수정
	SelectItem m_selectItem;
	EquipItem m_equipItem[5];
	Citem m_tempItem[5];

	int m_weaponCount;
	int m_armorCount;
	int m_shoesCount;
	int m_glovesCount;
	int m_pendantCount;

	Potion m_potion;

public:

	Cinventory();
	~Cinventory();

	HRESULT init();
	void release();
	void update();
	//void render();

	// 아이템 얻었을때
	void addItem(Citem* item);
	// 아이템 장착
	void equipItem();
	void setEquipRender(ITEMTYPE type, POINT renderPoint);
	// 아이템 장착 해제할때
	void UnEquipItem(Citem* item);
	// 아이템 버릴때
	void AbandonItem();

	Potion* getPotion() { return &m_potion; }
	void setPotion(int count) { m_potion.Count = count; }

	// 장착중인 아이템 리스트 
	vector<Citem*>* getvWeaponList() { return &m_vWeaponList; }
	void setvWeaponList(vector<Citem*>* weaponList) { m_vWeaponList = *weaponList; }
	vector<Citem*>* getvArmorList() { return &m_vArmorList; }
	void setvArmorList(vector<Citem*>* armorList) { m_vArmorList = *armorList; }
	vector<Citem*>* getvShoesList() { return &m_vShoesList; }
	void setvShoesList(vector<Citem*>* shoesList) { m_vShoesList = *shoesList; }
	vector<Citem*>* getvGlovesList() { return &m_vGlovesList; }
	void setvGlovesList(vector<Citem*>* glovesList) { m_vGlovesList = *glovesList; }
	vector<Citem*>* getvPendantList() { return &m_vPendantList; }
	void setvPendantList(vector<Citem*>* pendantList) { m_vPendantList = *pendantList; }


	EquipItem* getEquipItem() { return m_equipItem; }
	EquipItem* getEquipItem(ITEMTYPE type);
	void setEquipItem(EquipItem* equipItem);

	SelectItem* getSelectItem() { return &m_selectItem; }
	void setSelectItem(Citem* item, int index, POINT point, bool isSelect);

	void clearSelectItem();
	void clearEquipItem(ITEMTYPE type);
	//void setItemId();
};

