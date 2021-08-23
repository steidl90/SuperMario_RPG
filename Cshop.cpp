#include "framework.h"
#include "Cshop.h"
#include "Cplayer.h"
HRESULT Cshop::init()
{
	// �Ϲ� ��� �����۸� �����ͼ� push
	for (int i = 0; i < ITEM->getTotalItemCount(); i++)
	{
		if (ITEM->getItem(i)->getItemGradeInt() == 1) continue;

		m_vTotalList.push_back((ITEM->getItem(i)));
	}

	return S_OK;
}

void Cshop::release()
{
}

void Cshop::update()
{
}

void Cshop::buyItem(Citem* item)
{
	if (m_player->getGold() >= item->getBuyPrice())
	{
		m_myInventory->addItem(item);
		m_player->setGold(m_player->getGold() - item->getBuyPrice());
	}
}

void Cshop::sellItem()
{
	ITEMTYPE type = m_myInventory->getSelectItem()->m_item->getType();

	// ���� ������ Ÿ�԰� ���� ������ Ÿ�� ���� �κ��� ��
	if (m_myInventory->getEquipItem(type)->isEquip)
	{
		if (m_myInventory->getEquipItem(type)->m_item->getItemId()
			== m_myInventory->getSelectItem()->m_item->getItemId()) return;
		else
		{
			m_player->setGold(m_player->getGold() + m_myInventory->getSelectItem()->m_item->getBuyPrice());
			m_myInventory->AbandonItem();
			m_myInventory->clearSelectItem();
		}
	}
	else
	{
		m_player->setGold(m_player->getGold() + m_myInventory->getSelectItem()->m_item->getBuyPrice());
		m_myInventory->AbandonItem();
		m_myInventory->clearSelectItem();
	}
}
