#pragma once
#include"gameNode.h"
class Citem
{
private:
	string m_BigImage;
	string m_SmallImage;
	string m_Name;
	ITEMTYPE m_Type;
	int m_atk;
	int m_def;
	int m_hp;
	int m_mp;
	int m_critical;
	float m_criticalAtk;
	float m_speed;
	int m_limitLevel;
	int m_itemBuyPrice;
	POINT m_frame;
	int m_itemId;
	int m_itemGrade;

public:
	Citem();
	Citem(string bigImg, string smallImg, string name, ITEMTYPE type, int atk, int def, int hp, int mp,
		int cri, float criAtk, float speed, int level, int price, POINT frame, int itemId, int itemGrade);
	~Citem();

	string getBigImage()const { return m_BigImage; }
	string getSmallImage()const { return m_SmallImage; }
	string getName()const { return m_Name; }
	ITEMTYPE getType()const { return m_Type; }
	int getAtk()const { return m_atk; }
	int getDef()const { return m_def; }
	int getHp()const { return m_hp; }
	int getMp()const { return m_mp; }
	int getCritical()const { return m_critical; }
	float getCriticalAtk()const { return m_criticalAtk; }
	float getSpeed()const { return m_speed; }
	int getLimitLevel()const { return m_limitLevel; }
	int getBuyPrice()const { return m_itemBuyPrice; }
	POINT getFrame()const { return m_frame; }
	int getItemId()const { return m_itemId; }
	string getItemGrade()const;
	int getItemGradeInt()const { return m_itemGrade; }

	void setItemId(int id);

};

