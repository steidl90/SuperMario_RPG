#pragma once
#include"singleton.h"

class Citem;
class CplayerData : public Singleton<CplayerData>
{
private:
	int m_atk;
	int m_def;
	int m_hp;
	int m_maxHp;
	int m_mp;
	int m_maxMp;
	int m_critical;
	int m_lv;
	int m_exp;
	int m_gold;
	float m_criticalAtk;
	float m_speed;
	float m_x;
	float m_y;

	//퀘스트 데이터
	int m_quest, m_maxQuest;
	bool m_isDialog;
	bool m_isQuesting;
	bool m_isComplete;

	//보유 아이템
	vector<Citem*> m_vWeaponList;
	vector<Citem*> m_vArmorList;
	vector<Citem*> m_vShoesList;
	vector<Citem*> m_vGlovesList;
	vector<Citem*> m_vPendantList;
	
	//장착 아이템
	EquipItem m_equipItem[5];

public:
	CplayerData();
	~CplayerData();

	HRESULT init();
	void release();
	void update();
	void render();

	void setData(int atk, int def, int hp, int maxhp, int mp, int maxmp, int cri, int lv, int exp, int gold, float criatk, float speed, float x, float y);

	EquipItem* getEquipItem() { return m_equipItem; }
	void setEquipItem(EquipItem* equipItem);

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

	int getAtk() { return m_atk; }
	int getDef() { return m_def; }
	int getHp() { return m_hp; }
	int getMaxHp() { return m_maxHp; }
	int getMp() { return m_mp; }
	int getMaxMp() { return m_maxMp; }
	int getCritical() { return m_critical; }
	int getLv() { return m_lv; }
	int getExp() { return m_exp; }
	int getGold() { return m_gold; }
	float getCriticalAtk() { return m_criticalAtk; }
	float getSpeed() { return m_speed; }
	float getX() { return m_x; }
	float getY() { return m_y; }

	void setQuest(int quest) { m_quest = quest; }
	int getQuest() { return m_quest; }

	void setMaxQuest(int maxquest) { m_maxQuest = maxquest; }
	int getMaxQuest() { return m_maxQuest; }
	
	void setIsDialog(bool dialog) { m_isDialog = dialog; }
	bool getIsDialog() { return m_isDialog; }
	
	void setIsQuesting(bool questing) { m_isQuesting = questing; }
	bool getIsQuesting() { return m_isQuesting; }
	
	void setIsComplete(bool complete) { m_isComplete = complete; }
	bool getIsComplete() { return m_isComplete; }

};

