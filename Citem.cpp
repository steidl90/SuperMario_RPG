#include "framework.h"
#include "Citem.h"
Citem::Citem()
{
	OutputDebugString(_TEXT("Citem()\n"));
}

Citem::Citem(string bigImg, string smallImg, string name, ITEMTYPE type, int atk, int def, int hp, int mp, int cri, float criAtk, float speed, int level, int price, POINT frame, int itemId, int itemGrade)
	: m_BigImage(bigImg), m_SmallImage(smallImg), m_Name(name), m_Type(type), m_atk(atk), m_def(def), m_hp(hp), m_mp(mp)
	, m_critical(cri), m_criticalAtk(criAtk), m_speed(speed), m_limitLevel(level), m_itemBuyPrice(price), m_frame(frame)
	, m_itemId(itemId), m_itemGrade(itemGrade)
{
	OutputDebugString(_TEXT("Citem(...)\n"));
}

Citem::~Citem()
{
}

string Citem::getItemGrade() const
{
	string grade;
	if (m_itemGrade == 0)
		grade = "일반";
	else if (m_itemGrade == 1)
		grade = "전설";

	return grade;
}

void Citem::setItemId(int id)
{
	m_itemId += id;
}
