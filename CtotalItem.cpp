#include "framework.h"
#include "CtotalItem.h"
#include"Citem.h"

// ÃßÈÄ¿¡ ReadFile·Î ºÒ·¯¿Â °ªÀ¸·Î ¾ÆÀÌÅÛ Á¤º¸µé »ý¼º
HRESULT CtotalItem::init()
{
	// Å«ÀÌ¹ÌÁö / ÀÛÀºÀÌ¹ÌÁö / ÅÛÀÌ¸§ / Å¸ÀÔ / °ø°Ý·Â / ¹æ¾î·Â / Ã¼·Â / ¸¶³ª / Å©¸®À² /
	// Å©¸®µ¥¹ÌÁö / ½ºÇÇµå / Á¦ÇÑ·¹º§ / °¡°Ý / ÇÁ·¹ÀÓ x,y

	//Citem* inputItem = new Citem("¹«±âºò", "¹«±âºò", "ÀÏ¹Ý Ã¢", ITEMTYPE::ITEMTYPE_WEAPON, 30, 0, 0, 10, 20,
	//	20, 0, 10, 1000, PointMake(0, 0));
	//Citem* inputItem2 = new Citem("°©¿Êºò", "°©¿Ê½º¸ô", "ÀÏ¹Ý °©¿Ê", ITEMTYPE::ITEMTYPE_ARMOR, 0, 30, 100, 10, 0,
	//	0, 0, 10, 1000, PointMake(0, 0));
	//Citem* inputItem3 = new Citem("°©¿Êºò", "°©¿Ê½º¸ô", "°­È­ °©¿Ê", ITEMTYPE::ITEMTYPE_ARMOR, 0, 50, 200, 10, 0,
	//	0, 0, 15, 1500, PointMake(1, 0));
	//Citem* inputItem4 = new Citem("¹«±âºò", "¹«±âºò", "°­È­ Ã¢", ITEMTYPE::ITEMTYPE_WEAPON, 50, 0, 0, 20, 30,
	//	30, 0, 15, 1500, PointMake(1, 0));

	itemList = TXT->txtLoad("¾ÆÀÌÅÛ¸®½ºÆ®2.csv");

	this->itemInit();

	return S_OK;
}

void CtotalItem::release()
{
}
void CtotalItem::update(){}

void CtotalItem::render(){}

void CtotalItem::itemInit()
{
	m_itemCount = itemList.size();

	for (int i = 0; i < m_itemCount; i+=15)
	{
		m_name = itemList[i];

		if (stoi(itemList[i+1]) == 0)
		{
			m_bigImage = "¹«±âºò";
			m_smallImage = "¹«±â½º¸ô";
			m_Type = ITEMTYPE::ITEMTYPE_WEAPON;
		}
		else if (stoi(itemList[i+1]) == 1)
		{
			m_bigImage = "°©¿Êºò";
			m_smallImage = "°©¿Ê½º¸ô";
			m_Type = ITEMTYPE::ITEMTYPE_ARMOR;
		}
		else if (stoi(itemList[i + 1]) == 2)
		{
			m_bigImage = "½Å¹ßºò";
			m_smallImage = "½Å¹ß½º¸ô";
			m_Type = ITEMTYPE::ITEMTYPE_SHOES;
		}
		else if (stoi(itemList[i + 1]) == 3)
		{
			m_bigImage = "Àå°©ºò";
			m_smallImage = "Àå°©½º¸ô";
			m_Type = ITEMTYPE::ITEMTYPE_GLOVES;
		}
		else if (stoi(itemList[i + 1]) == 4)
		{
			m_bigImage = "Ææ´øÆ®ºò";
			m_smallImage = "Ææ´øÆ®½º¸ô";
			m_Type = ITEMTYPE::ITEMTYPE_PENDANT;
		}
		m_atk = stoi(itemList[i+2]);
		m_def = stoi(itemList[i+3]);
		m_hp = stoi(itemList[i+4]);
		m_mp = stoi(itemList[i+5]);
		m_critical = stoi(itemList[i+6]);
		m_criticalAtk = stof(itemList[i+7]);
		m_speed = stof(itemList[i+8]);
		m_limitLevel = stoi(itemList[i+9]);
		m_itemBuyPrice = stoi(itemList[i+10]);
		m_frame = PointMake(stoi(itemList[i + 11]), stoi(itemList[i + 12]));
		m_itemId = stoi(itemList[i + 13]);
		m_itemGrade = stoi(itemList[i + 14]);

		Citem* inputItem = new Citem(m_bigImage, m_smallImage, m_name, m_Type, m_atk, m_def,
			m_hp, m_mp, m_critical, m_criticalAtk, m_speed, m_limitLevel, m_itemBuyPrice, m_frame
			,m_itemId, m_itemGrade);

		m_totalItem.push_back(inputItem);
	}
}

// index¸¦ ÅëÇØ ÇÊ¿äÇÑ ¾ÆÀÌÅÛ return - ÀÓ½Ã¹æ¹ý
Citem* CtotalItem::getItem(int index)
{
	return m_totalItem[index];
}