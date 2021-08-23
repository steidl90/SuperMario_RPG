#pragma once
#include"rootHeader.h"
#include"singleton.h"

class Citem;
class CtotalItem : public Singleton<CtotalItem>
{
	vector<Citem*> m_totalItem;
	vector<string> itemList;

	string m_bigImage;
	string m_smallImage;
	string m_name;
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

	int m_itemCount;
public:
	HRESULT init();
	void release();
	void update();
	void render();

	void itemInit();

	int getTotalItemCount()const { return m_itemCount / 15; }
	Citem* getItem(int index);
};

