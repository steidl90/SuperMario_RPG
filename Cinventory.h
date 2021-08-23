#pragma once
#include"Citem.h"



class Cinventory
{
	vector<Citem*> m_vWeaponList;
	vector<Citem*> m_vArmorList;
	vector<Citem*> m_vShoesList;
	vector<Citem*> m_vGlovesList;
	vector<Citem*> m_vPendantList;

	// ��� ���� �������
	// ���� ����
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

	// ������ �������
	void addItem(Citem* item);
	// ������ ����
	void equipItem();
	void setEquipRender(ITEMTYPE type, POINT renderPoint);
	// ������ ���� �����Ҷ�
	void UnEquipItem(Citem* item);
	// ������ ������
	void AbandonItem();

	Potion* getPotion() { return &m_potion; }
	void setPotion(int count) { m_potion.Count = count; }

	// �������� ������ ����Ʈ 
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

