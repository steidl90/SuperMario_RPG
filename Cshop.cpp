#include "framework.h"
#include "Cshop.h"
#include "Cplayer.h"
HRESULT Cshop::init()
{
	// 일반 등급 아이템만 가져와서 push
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

	// 선택 아이템 타입과 장착 아이템 타입 같은 부분을 비교
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
