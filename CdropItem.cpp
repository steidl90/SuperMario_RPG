#include "framework.h"
#include "CdropItem.h"
#include "Citem.h"
HRESULT CdropItem::init()
{
	for (int i = 0; i < ITEM->getTotalItemCount(); i++)
	{
		m_vDropItemList.push_back((ITEM->getItem(i)));
	}
	return S_OK;
}

void CdropItem::release()
{
}

void CdropItem::update()
{
}

void CdropItem::render()
{
	TCHAR str[128];
	for (m_viDropItem = m_vDropItem.begin(); m_viDropItem != m_vDropItem.end(); ++m_viDropItem)
	{
		// Rectangle(getMapDC(), m_viDropItem->itemRect.left, m_viDropItem->itemRect.top, m_viDropItem->itemRect.right, m_viDropItem->itemRect.bottom);
		IMAGE->findImage(m_viDropItem->item->getSmallImage())->frameRender(getMapDC()
			, m_viDropItem->itemRect.left, m_viDropItem->itemRect.top
			, m_viDropItem->item->getFrame().x, m_viDropItem->item->getFrame().y);

		sprintf_s(str, "%s", m_viDropItem->item->getName().c_str());
		SetBkMode(getMapDC(), TRANSPARENT);
		SetTextColor(getMapDC(), RGB(255, 255, 255));
		TextOut(getMapDC(), m_viDropItem->x - (IMAGE->findImage(m_viDropItem->item->getSmallImage())->getFrameWidth() / 2), m_viDropItem->y - 10, str, lstrlen(str));
	}
}

Citem* CdropItem::getItem()
{
	int isDrop, itemType, dropItem = 0;
	isDrop = RND->getInt(2);
	itemType = RND->getInt(5);


	/*if (isDrop == 1)
	{*/
		if (itemType == 0) // ¹«±â
		{
			dropItem = RND->getFromIntTo(1, 5);
		}
		else if (itemType == 1) // °©¿Ê
		{
			dropItem = RND->getFromIntTo(8, 12);
		}
		else if (itemType == 2) // ½Å¹ß
		{
			dropItem = RND->getFromIntTo(15, 19);
		}
		else if (itemType == 3) // Àå°©
		{
			dropItem = RND->getFromIntTo(22, 26);
		}
		else if (itemType == 4) // ¾Ç¼¼
		{
			dropItem = RND->getFromIntTo(29, 33);
		}

   		return m_vDropItemList[dropItem];
	//}
	/*else
	{
		return m_vDropItemList[0];
	}*/

}

void CdropItem::makeItem(float x, float y)
{
	//if (this->getItem()->getItemId() == m_vDropItemList[0]->getItemId()) return;

	DropItem tempItem;
	tempItem.item = this->getItem();
	tempItem.itemRect = RectMake(x, y, IMAGE->findImage(tempItem.item->getSmallImage())->getFrameWidth(),
		IMAGE->findImage(tempItem.item->getSmallImage())->getFrameHeight());
	tempItem.x = x;
	tempItem.y = y;
	m_vDropItem.push_back(tempItem);
}

void CdropItem::makeFinalItem(float x, float y)
{
	DropItem finalItem, finalItem2, finalItem3, finalItem4, finalItem5;

	finalItem.item = m_vDropItemList[6];
	finalItem.itemRect = RectMake(x - 50, y + 200, IMAGE->findImage(finalItem.item->getSmallImage())->getFrameWidth(),
		IMAGE->findImage(finalItem.item->getSmallImage())->getFrameHeight());
	finalItem.x = x - 50;
	finalItem.y = y + 200;
	m_vDropItem.push_back(finalItem);

	finalItem2.item = m_vDropItemList[13];
	finalItem2.itemRect = RectMake(x + 50, y + 150, IMAGE->findImage(finalItem2.item->getSmallImage())->getFrameWidth(),
		IMAGE->findImage(finalItem2.item->getSmallImage())->getFrameHeight());
	finalItem2.x = x + 50;
	finalItem2.y = y + 150;
	m_vDropItem.push_back(finalItem2);

	finalItem3.item = m_vDropItemList[20];
	finalItem3.itemRect = RectMake(x + 150, y + 200, IMAGE->findImage(finalItem3.item->getSmallImage())->getFrameWidth(),
		IMAGE->findImage(finalItem3.item->getSmallImage())->getFrameHeight());
	finalItem3.x = x + 150;
	finalItem3.y = y + 200;
	m_vDropItem.push_back(finalItem3);

	finalItem4.item = m_vDropItemList[27];
	finalItem4.itemRect = RectMake(x, y + 250, IMAGE->findImage(finalItem4.item->getSmallImage())->getFrameWidth(),
		IMAGE->findImage(finalItem4.item->getSmallImage())->getFrameHeight());
	finalItem4.x = x;
	finalItem4.y = y + 250;
	m_vDropItem.push_back(finalItem4);

	finalItem5.item = m_vDropItemList[34];
	finalItem5.itemRect = RectMake(x + 100, y + 250, IMAGE->findImage(finalItem5.item->getSmallImage())->getFrameWidth(),
		IMAGE->findImage(finalItem5.item->getSmallImage())->getFrameHeight());
	finalItem5.x = x + 100;
	finalItem5.y = y + 250;
	m_vDropItem.push_back(finalItem5);
}

void CdropItem::removeItem(int num)
{
	m_vDropItem.erase(m_vDropItem.begin() + num);
}
