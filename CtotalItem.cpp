#include "framework.h"
#include "CtotalItem.h"
#include"Citem.h"

// ���Ŀ� ReadFile�� �ҷ��� ������ ������ ������ ����
HRESULT CtotalItem::init()
{
	// ū�̹��� / �����̹��� / ���̸� / Ÿ�� / ���ݷ� / ���� / ü�� / ���� / ũ���� /
	// ũ�������� / ���ǵ� / ���ѷ��� / ���� / ������ x,y

	//Citem* inputItem = new Citem("�����", "�����", "�Ϲ� â", ITEMTYPE::ITEMTYPE_WEAPON, 30, 0, 0, 10, 20,
	//	20, 0, 10, 1000, PointMake(0, 0));
	//Citem* inputItem2 = new Citem("���ʺ�", "���ʽ���", "�Ϲ� ����", ITEMTYPE::ITEMTYPE_ARMOR, 0, 30, 100, 10, 0,
	//	0, 0, 10, 1000, PointMake(0, 0));
	//Citem* inputItem3 = new Citem("���ʺ�", "���ʽ���", "��ȭ ����", ITEMTYPE::ITEMTYPE_ARMOR, 0, 50, 200, 10, 0,
	//	0, 0, 15, 1500, PointMake(1, 0));
	//Citem* inputItem4 = new Citem("�����", "�����", "��ȭ â", ITEMTYPE::ITEMTYPE_WEAPON, 50, 0, 0, 20, 30,
	//	30, 0, 15, 1500, PointMake(1, 0));

	itemList = TXT->txtLoad("�����۸���Ʈ2.csv");

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
			m_bigImage = "�����";
			m_smallImage = "���⽺��";
			m_Type = ITEMTYPE::ITEMTYPE_WEAPON;
		}
		else if (stoi(itemList[i+1]) == 1)
		{
			m_bigImage = "���ʺ�";
			m_smallImage = "���ʽ���";
			m_Type = ITEMTYPE::ITEMTYPE_ARMOR;
		}
		else if (stoi(itemList[i + 1]) == 2)
		{
			m_bigImage = "�Źߺ�";
			m_smallImage = "�Ź߽���";
			m_Type = ITEMTYPE::ITEMTYPE_SHOES;
		}
		else if (stoi(itemList[i + 1]) == 3)
		{
			m_bigImage = "�尩��";
			m_smallImage = "�尩����";
			m_Type = ITEMTYPE::ITEMTYPE_GLOVES;
		}
		else if (stoi(itemList[i + 1]) == 4)
		{
			m_bigImage = "���Ʈ��";
			m_smallImage = "���Ʈ����";
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

// index�� ���� �ʿ��� ������ return - �ӽù��
Citem* CtotalItem::getItem(int index)
{
	return m_totalItem[index];
}