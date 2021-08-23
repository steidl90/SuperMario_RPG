#include "framework.h"
#include "Cinventory.h"

Cinventory::Cinventory()
{
}

Cinventory::~Cinventory()
{
}

HRESULT Cinventory::init()
{
	// 일단 push할때 타입 예외처리 안함.. 그냥 실험용


	for (int i = 0; i < 5; i++)
	{
		ZeroMemory(&m_equipItem[i], sizeof(EquipItem));
		ZeroMemory(&m_selectItem, sizeof(SelectItem));
	}

	//m_potion.image
	m_potion.Count = 20;
	m_potion.recoveryHp = 200;
	m_potion.recoveryMp = 300;

	m_weaponCount = 0;
	m_armorCount = 0;
	m_shoesCount = 0;
	m_glovesCount = 0;
	m_pendantCount = 0;
	return S_OK;
}

void Cinventory::release()
{
}

void Cinventory::update()
{
}

void Cinventory::addItem(Citem* item)
{
	Citem* tempItem = new Citem(item->getBigImage(), item->getSmallImage(), item->getName(), item->getType(), item->getAtk(),
		item->getDef(), item->getHp(), item->getMp(), item->getCritical(), item->getCriticalAtk(), item->getSpeed(), item->getLimitLevel(),
		item->getBuyPrice(), item->getFrame(), item->getItemId(), item->getItemGradeInt());

	switch (item->getType())
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		m_weaponCount++;
		tempItem->setItemId(m_weaponCount);
		m_vWeaponList.push_back(tempItem);
		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		m_armorCount++;
		tempItem->setItemId(m_armorCount);
		m_vArmorList.push_back(tempItem);
		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		m_shoesCount++;
		tempItem->setItemId(m_shoesCount);
		m_vShoesList.push_back(tempItem);
		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		m_glovesCount++;
		tempItem->setItemId(m_glovesCount);
		m_vGlovesList.push_back(tempItem);
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		m_pendantCount++;
		tempItem->setItemId(m_pendantCount);
		m_vPendantList.push_back(tempItem);
		break;
	default:
		break;
	}
}

// 랜더 포인트는 다른곳에서
void Cinventory::equipItem()
{
	if (m_selectItem.m_item != nullptr)
	{
		m_tempItem[static_cast<int>(m_selectItem.m_item->getType())] = *m_selectItem.m_item;
		ITEMTYPE type = m_selectItem.m_item->getType();
		m_equipItem[static_cast<int>(type)].isEquip = true;
		m_equipItem[static_cast<int>(type)].m_item = &m_tempItem[static_cast<int>(m_selectItem.m_item->getType())];
		m_equipItem[static_cast<int>(type)].m_itemIndex = m_selectItem.m_itemIndex;
	}
}

void Cinventory::setEquipRender(ITEMTYPE type, POINT renderPoint)
{
	m_equipItem[static_cast<int>(type)].m_renderPoint = renderPoint;
}


void Cinventory::UnEquipItem(Citem* item)
{
}


// 제거할때 고유 아이디로 제거해야할 필요가 있음.. 지금은 일단 동일 이름기준 제거
void Cinventory::AbandonItem()
{
	if (m_selectItem.isSelect == false)
		return;

	ITEMTYPE type = m_selectItem.m_item->getType();
	if (m_equipItem[static_cast<int>(type)].isEquip)
	{
		if (m_equipItem[static_cast<int>(type)].m_item->getItemId() == m_selectItem.m_item->getItemId())
			return;
	}

	if (m_equipItem[static_cast<int>(type)].isEquip)
	{
		if (m_equipItem[static_cast<int>(type)].m_itemIndex > m_selectItem.m_itemIndex)
			m_equipItem[static_cast<int>(type)].m_itemIndex--;
	}

	switch (type)
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		for (auto iter = m_vWeaponList.begin(); iter != m_vWeaponList.end(); ++iter)
		{
			if ((*iter)->getItemId() == m_selectItem.m_item->getItemId())
			{
				Citem* temp = *iter;
				m_vWeaponList.erase(iter);
				SAFE_DELETE(temp);
				break;
			}
		}
		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		for (auto iter = m_vArmorList.begin(); iter != m_vArmorList.end(); ++iter)
		{
			if ((*iter)->getItemId() == m_selectItem.m_item->getItemId())
			{
				Citem* temp = *iter;
				m_vArmorList.erase(iter);
				SAFE_DELETE(temp);
				break;
			}
		}
		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		for (auto iter = m_vGlovesList.begin(); iter != m_vGlovesList.end(); ++iter)
		{
			if ((*iter)->getItemId() == m_selectItem.m_item->getItemId())
			{
				Citem* temp = *iter;
				m_vGlovesList.erase(iter);
				SAFE_DELETE(temp);
				break;
			}
		}
		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		for (auto iter = m_vShoesList.begin(); iter != m_vShoesList.end(); ++iter)
		{
			if ((*iter)->getItemId() == m_selectItem.m_item->getItemId())
			{
				Citem* temp = *iter;
				m_vShoesList.erase(iter);
				SAFE_DELETE(temp);
				break;
			}
		}
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		for (auto iter = m_vPendantList.begin(); iter != m_vPendantList.end(); ++iter)
		{
			if ((*iter)->getItemId() == m_selectItem.m_item->getItemId())
			{
				Citem* temp = *iter;
				m_vPendantList.erase(iter);
				SAFE_DELETE(temp);
				break;
			}
		}
		break;
	}
}

void Cinventory::setEquipItem(EquipItem* equipItem)
{
	m_equipItem[0] = equipItem[0];
	m_equipItem[1] = equipItem[1];
	m_equipItem[2] = equipItem[2];
	m_equipItem[3] = equipItem[3];
	m_equipItem[4] = equipItem[4];
}


EquipItem* Cinventory::getEquipItem(ITEMTYPE type)
{
	return &m_equipItem[static_cast<int>(type)];
}


void Cinventory::setSelectItem(Citem* item, int index, POINT point, bool isSelect)
{
	m_selectItem.m_item = item;
	m_selectItem.m_itemIndex = index;
	m_selectItem.m_renderPoint = point;
	m_selectItem.isSelect = isSelect;
}

void Cinventory::clearSelectItem()
{
	ZeroMemory(&m_selectItem, sizeof(SelectItem));
}

void Cinventory::clearEquipItem(ITEMTYPE type)
{
	ZeroMemory(&m_equipItem[static_cast<int>(type)], sizeof(EquipItem));
}

//// 사실 인벤토리에서 아이템 생성은 임시.. 상점에서 해야할일 일단 무기만 적용
//// 뭔가 이상
//void Cinventory::setItemId()
//{
//	int i = 0;
//	for (auto iter = m_vWeaponList.begin(); iter != m_vWeaponList.end(); ++iter)
//	{
//		(*iter).setItemId(i);
//		i++;
//	}
//}
