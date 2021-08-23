#include "framework.h"
#include "CshopUi.h"
#include "Cplayer.h"
HRESULT CshopUi::init()
{
	m_shopUiX = 100;
	m_shopUiY = 150;

	m_shopRect = RectMake(m_shopUiX, m_shopUiY, IMAGE->findImage("����â")->getWidth(), IMAGE->findImage("����â")->getHeight());

	m_shopListX = m_shopUiX + 20;
	m_shopListY = m_shopUiY + 25;

	for (int i = 0; i < 6; i++)
	{
		RECT temp;
		temp = RectMake(m_shopListX, m_shopListY + i * 43, 200, 40);
		m_vShopListRect.push_back(temp);
	}

	m_shopInfoX = m_shopUiX + 250;
	m_shopInfoY = m_shopUiY + 35;

	m_shopInfo = RectMake(m_shopInfoX, m_shopInfoY, 200, 80);

	m_shopButtonX = m_shopUiX + 30;
	m_shopButtonY = m_shopUiY + 390;

	m_buyButton = RectMake(m_shopButtonX, m_shopButtonY, 80, 50);

	m_exitButton = RectMake(m_shopButtonX + 120, m_shopButtonY, 80, 50);

	m_inventoryUiX = 570;
	m_inventoryUiY = 150;

	m_inventoryRect = RectMake(m_inventoryUiX, m_inventoryUiY, IMAGE->findImage("�κ��丮1")->getWidth(), IMAGE->findImage("�κ��丮1")->getHeight());
	
	m_itemListX = m_inventoryUiX + 20;
	m_itemListY = m_inventoryUiY + 25;

	for (int i = 0; i < 4; i++)
	{
		RECT temp;
		temp = RectMake(m_itemListX, m_itemListY + i * 88, 200, 80);
		m_vItemListRect.push_back(temp);
	}

	m_itemInfoX = m_inventoryUiX + 250;
	m_itemInfoY = m_inventoryUiY + 35;

	m_ItemInfoRect = RectMake(m_itemInfoX, m_itemInfoY, 200, 80);

	m_inventoryButtonX = m_inventoryUiX + 30;
	m_inventoryButtonY = m_inventoryUiY + 390;

	m_sellButton = RectMake(m_inventoryButtonX, m_inventoryButtonY, 70, 20);


	m_selectType = ITEMTYPE::ITEMTYPE_WEAPON;
	m_showIndex = 0;
	isSelectShop = false;
	isSelectRender = false;

	isButtonClick = false;
	isKeyUp = true;
	m_exit = false;

	return S_OK;
}

void CshopUi::release()
{
}

void CshopUi::update()
{
	this->selectItem();
	this->selectShopItem();

	if (InputManager->isStayKeyDown(VK_LBUTTON)) isButtonClick = true;
	else
	{
		isButtonClick = false;
		isKeyUp = true;
	}
	if (isButtonClick)
	{
		if (isKeyUp)
		{
			this->buyItem();
			this->sellItem();
			this->exitShop();
		}
	}
	if (m_shop->getShopSelectItem() != nullptr) m_selectType = m_shop->getShopSelectItem()->getType();

	this->setShowIndex();
}

void CshopUi::render()
{
	IMAGE->findImage("����â")->render(getMemDC(), m_shopRect.left, m_shopRect.top);
	IMAGE->findImage("�κ��丮1")->render(getMemDC(), m_inventoryRect.left, m_inventoryRect.top);

	for (auto iter = m_vShopListRect.begin(); iter != m_vShopListRect.end(); ++iter)
	{
		//Rectangle(getMemDC(), (*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
	}

	for (auto iter = m_vItemListRect.begin(); iter != m_vItemListRect.end(); ++iter)
	{
		//Rectangle(getMemDC(), (*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
	}

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_sellButton.left + 10, m_sellButton.top + 5, TEXT("�Ǹ�"), lstrlen("�Ǹ�"));
	TextOut(getMemDC(), m_buyButton.left + 10, m_buyButton.top + 5, TEXT("����"), lstrlen("����"));
	TextOut(getMemDC(), m_exitButton.left + 10, m_exitButton.top + 5, TEXT("������"), lstrlen("������"));
	char strGold[100];
	wsprintf(strGold, "�����ݾ�: %d gold", m_shop->getPlayer()->getGold());
	TextOut(getMemDC(), m_sellButton.left + 10, m_sellButton.top + 35, strGold, lstrlen(strGold));
	
	//Rectangle(getMemDC(), m_ItemInfoRect.left, m_ItemInfoRect.top, m_ItemInfoRect.right, m_ItemInfoRect.bottom);


	this->showItemType();

	this->showEquipSelect();

	if (isSelectRender)
	{
		IMAGE->findImage("�����׵θ�")->render(getMemDC(), m_selectRenderX, m_selectRenderY);
		this->showItemInfo();
	}

	if (isSelectShop)
		this->showShopInfo();

	this->showShopItemList(m_shop->getTotalList());
}


void CshopUi::showInvenItemList(vector<Citem*>* item)
{
	char str[100];

	// show �ε����� �⺻ 0~3������ �����ش�, ���� ��ũ�ѷ� 1~4 �̷������� �����ֱ�
	int	i = m_showIndex;
	int j = 0;
	vector<Citem*>::iterator iter;
	for (iter = item->begin() + i; i < m_showEndIndex; ++iter, i++, j++)
	{
		IMAGE->findImage((*iter)->getSmallImage())->frameRender(getMemDC()
			, m_vItemListRect[j].left, m_vItemListRect[j].top, (*iter)->getFrame().x, (*iter)->getFrame().y);

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), m_vItemListRect[j].left + 80, m_vItemListRect[j].top + 10, (*iter)->getName().c_str(), lstrlen((*iter)->getName().c_str()));
		wsprintf(str, "�ʿ� ����: %d", (*iter)->getLimitLevel());
		TextOut(getMemDC(), m_vItemListRect[j].left + 80, m_vItemListRect[j].top + 30, str, lstrlen(str));
		wsprintf(str, "���: %d", (*iter)->getBuyPrice());
		TextOut(getMemDC(), m_vItemListRect[j].left + 80, m_vItemListRect[j].top + 50, str, lstrlen(str));
	}
}

void CshopUi::showItemInfo()
{
	char str[100];

	IMAGE->findImage(m_shop->getInventory()->getSelectItem()->m_item ->getSmallImage())->frameRender(getMemDC(), m_ItemInfoRect.left + 11, m_ItemInfoRect.top
		, m_shop->getInventory()->getSelectItem()->m_item->getFrame().x, m_shop->getInventory()->getSelectItem()->m_item->getFrame().y);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 10, m_shop->getInventory()->getSelectItem()->m_item->getName().c_str(), lstrlen(m_shop->getInventory()->getSelectItem()->m_item->getName().c_str()));
	wsprintf(str, "�ʿ� ����: %d", m_shop->getInventory()->getSelectItem()->m_item->getLimitLevel());
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 30, str, lstrlen(str));
	wsprintf(str, "���: %d", m_shop->getInventory()->getSelectItem()->m_item->getBuyPrice());
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 50, str, lstrlen(str));
	
	this->itemStatInfo();


}

void CshopUi::itemStatInfo()
{
	char grade[100];
	char atk[100];
	char def[100];
	char hp[100];
	char mp[100];
	char cri[100];
	char criAtk[100];
	char speed[100];
	char level[100];
	
	wsprintf(grade, "��� : %s", m_shop->getInventory()->getSelectItem()->m_item->getItemGrade().c_str());
	wsprintf(atk, "���ݷ�: %d", m_shop->getInventory()->getSelectItem()->m_item->getAtk());
	wsprintf(def, "����: %d", m_shop->getInventory()->getSelectItem()->m_item->getDef());
	wsprintf(hp, "HP: %d", m_shop->getInventory()->getSelectItem()->m_item->getHp());
	wsprintf(mp, "MP: %d", m_shop->getInventory()->getSelectItem()->m_item->getMp());
	wsprintf(cri, "ũ����: %d%", m_shop->getInventory()->getSelectItem()->m_item->getCritical());
	sprintf(criAtk, "ũ�����ݷ�: %.1f", m_shop->getInventory()->getSelectItem()->m_item->getCriticalAtk());
	sprintf(speed, "�̵��ӵ�: %.1f", m_shop->getInventory()->getSelectItem()->m_item->getSpeed());
	wsprintf(level, "���ѷ���: %d", m_shop->getInventory()->getSelectItem()->m_item->getLimitLevel());

	switch (m_shop->getInventory()->getSelectItem()->m_item->getType())
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_ItemInfoRect.left + 10, m_ItemInfoRect.top + 280, level, lstrlen(level));
		break;
	default:
		break;
	}
}

void CshopUi::showItemType()
{
	switch (m_selectType)
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		showInvenItemList(m_shop->getInventory()->getvWeaponList());
		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		showInvenItemList(m_shop->getInventory()->getvArmorList());
		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		showInvenItemList(m_shop->getInventory()->getvShoesList());
		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		showInvenItemList(m_shop->getInventory()->getvGlovesList());
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		showInvenItemList(m_shop->getInventory()->getvPendantList());
		break;
	default:
		break;
	}
}

// ���� ����ó�� �ϼ� �ȵ�.. ��ũ�� ������ �������� ����ó�� �ʿ�
void CshopUi::setShowIndex()
{
	switch (m_selectType)
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		if (m_shop->getInventory()->getvWeaponList()->size() < 4)
		{
			m_showIndex = 0;
			m_showEndIndex = m_shop->getInventory()->getvWeaponList()->size();
		}
		else if (m_shop->getInventory()->getvWeaponList()->size() - 4 < m_showIndex)
		{
			m_showIndex = m_shop->getInventory()->getvWeaponList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;

		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		if (m_shop->getInventory()->getvArmorList()->size() < 4)
		{
			m_showIndex = 0;
			m_showEndIndex = m_shop->getInventory()->getvArmorList()->size();
		}
		else if (m_shop->getInventory()->getvArmorList()->size() - 4 < m_showIndex)
		{
			m_showIndex = m_shop->getInventory()->getvArmorList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;
		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		if (m_shop->getInventory()->getvShoesList()->size() < 4)
		{
			m_showIndex = 0;
			m_showEndIndex = m_shop->getInventory()->getvShoesList()->size();
		}
		else if (m_shop->getInventory()->getvShoesList()->size() - 4 < m_showIndex)
		{
			m_showIndex = m_shop->getInventory()->getvShoesList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;
		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		if (m_shop->getInventory()->getvGlovesList()->size() < 4)
		{
			m_showIndex = 0;
			m_showEndIndex = m_shop->getInventory()->getvGlovesList()->size();
		}
		else if (m_shop->getInventory()->getvGlovesList()->size() - 4 < m_showIndex)
		{
			m_showIndex = m_shop->getInventory()->getvGlovesList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		if (m_shop->getInventory()->getvPendantList()->size() < 4)
		{
			m_showIndex = 0;
			m_showEndIndex = m_shop->getInventory()->getvPendantList()->size();
		}
		else if (m_shop->getInventory()->getvPendantList()->size() - 4 < m_showIndex)
		{
			m_showIndex = m_shop->getInventory()->getvPendantList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;
		break;
	}
}

// �κ��丮 ������ ����
// TODO:: ������Ÿ�� �߰��ʿ�

void CshopUi::selectItem()
{
	vector<Citem*>::iterator itemIter;
	int i = m_showIndex;
	for (auto iter = m_vItemListRect.begin(); i < m_showEndIndex; ++iter, i++)
	{
		if (PtInRect(&(*iter), m_ptMouse))
		{
			if (isButtonClick)
			{
				if (isKeyUp)
				{
					isSelectRender = true;
					m_selectRenderX = (*iter).left - 5;
					m_selectRenderY = (*iter).top - 3;

					// ������ ������ ���� inventory ���� �����ͼ� selectItem ������ ���
					switch (m_selectType)
					{
					case ITEMTYPE::ITEMTYPE_WEAPON:
						itemIter = m_shop->getInventory()->getvWeaponList()->begin() + i;
						break;
					case ITEMTYPE::ITEMTYPE_ARMOR:
						itemIter = m_shop->getInventory()->getvArmorList()->begin() + i;
						break;
					case ITEMTYPE::ITEMTYPE_SHOES:
						itemIter = m_shop->getInventory()->getvShoesList()->begin() + i;
						break;
					case ITEMTYPE::ITEMTYPE_GLOVES:
						itemIter = m_shop->getInventory()->getvGlovesList()->begin() + i;
						break;
					case ITEMTYPE::ITEMTYPE_PENDANT:
						itemIter = m_shop->getInventory()->getvPendantList()->begin() + i;
						break;
					}

					m_shop->getInventory()->setSelectItem((*itemIter), i, PointMake(m_selectRenderX, m_selectRenderY), true);
					isKeyUp = false;
				}
			}
		}
	}
}

// ���� �������� �����۵��� myInventory���� ���� �������� -> �ش� ������ �ε����� ���� �����׵θ� ǥ��... 
void CshopUi::showEquipSelect()
{
	int renderIndex;
	int m_equipRenderX;
	int m_equipRenderY;
	bool isEquipSelectRender = true;
	//renderIndex = m_equipItem[static_cast<int>(m_selectType)].m_itemIndex - m_showIndex;
	renderIndex = m_shop->getInventory()->getEquipItem(m_selectType)->m_itemIndex - m_showIndex;
	if (renderIndex < 0 || renderIndex > 3)
		isEquipSelectRender = false;
	for (int i = 0; i < 4; i++)
	{
		if (i == renderIndex)
		{
			m_equipRenderX = m_vItemListRect[i].left - 5;
			m_equipRenderY = m_vItemListRect[i].top - 3;
			m_shop->getInventory()->setEquipRender(m_selectType, PointMake(m_equipRenderX, m_equipRenderY));
		}
	}

	if (isEquipSelectRender)
	{
		if (m_shop->getInventory()->getEquipItem(m_selectType)->isEquip)
			IMAGE->findImage("�����׵θ�")->render(getMemDC(), m_shop->getInventory()->getEquipItem(m_selectType)->m_renderPoint.x,
				m_shop->getInventory()->getEquipItem(m_selectType)->m_renderPoint.y);
	}
}


void CshopUi::sellItem()
{
	if (PtInRect(&m_sellButton, m_ptMouse))
	{
		if (m_shop->getInventory()->getSelectItem()->m_item != nullptr)
		{
			m_shop->sellItem();
			isSelectRender = false;
		}
		isKeyUp = false;
	}
}

void CshopUi::buyItem()
{
	if (PtInRect(&m_buyButton, m_ptMouse))
	{
		if (m_shop->getShopSelectItem() != nullptr)
		{
			m_shop->buyItem(m_shop->getShopSelectItem());
		}
		isKeyUp = false;
	}
}

void CshopUi::exitShop()
{
	if (PtInRect(&m_exitButton, m_ptMouse))
	{
		m_shop->getInventory()->clearSelectItem();
		m_exit = true;
	}
}

void CshopUi::showShopItemList(vector<Citem*>* item)
{
	char str[100];

	int i = 0;
	for (auto iter = item->begin(); iter != item->end(); ++iter, i++)
	{
		IMAGE->findImage((*iter)->getSmallImage())->frameRender(getMemDC()
			, m_vShopListRect[i].left, m_vShopListRect[i].top, (*iter)->getFrame().x, (*iter)->getFrame().y);

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), m_vShopListRect[i].left + 40, m_vShopListRect[i].top + 15, (*iter)->getName().c_str(), lstrlen((*iter)->getName().c_str()));
	/*	wsprintf(str, "�ʿ� ����: %d", (*iter).getLimitLevel());
		TextOut(getMemDC(), m_vShopListRect[i].left + 80, m_vShopListRect[i].top + 30, str, lstrlen(str));*/
		wsprintf(str, "���: %d", (*iter)->getBuyPrice());
		TextOut(getMemDC(), m_vShopListRect[i].left + 130, m_vShopListRect[i].top + 15, str, lstrlen(str));
	}
}

void CshopUi::selectShopItem()
{
	vector<Citem*>::iterator shopItemIter;

	int i = 0;
	for (auto iter = m_vShopListRect.begin(); iter != m_vShopListRect.end() && i < 5; ++iter, i++)
	{
		if (PtInRect(&(*iter), m_ptMouse))
		{
			if (InputManager->isOnceKeyDown(VK_LBUTTON))
			{
				isSelectShop = true;
				shopItemIter = m_shop->getTotalList()->begin() + i;
				m_shop->setShopSelectItem((*shopItemIter));

				m_shop->getInventory()->clearSelectItem();
				isSelectRender = false;
			}
		}
	}
}

void CshopUi::showShopInfo()
{
	char str[100];

	IMAGE->findImage(m_shop->getShopSelectItem()->getSmallImage())->frameRender(getMemDC(), m_shopInfo.left + 11, m_shopInfo.top
		, m_shop->getShopSelectItem()->getFrame().x, m_shop->getShopSelectItem()->getFrame().y);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_shopInfo.left + 80, m_shopInfo.top + 10, m_shop->getShopSelectItem()->getName().c_str(), lstrlen(m_shop->getShopSelectItem()->getName().c_str()));
	wsprintf(str, "�ʿ� ����: %d", m_shop->getShopSelectItem()->getLimitLevel());
	TextOut(getMemDC(), m_shopInfo.left + 80, m_shopInfo.top + 30, str, lstrlen(str));
	wsprintf(str, "���: %d", m_shop->getShopSelectItem()->getBuyPrice());
	TextOut(getMemDC(), m_shopInfo.left + 80, m_shopInfo.top + 50, str, lstrlen(str));

	this->shopItemStatInfo();
}

void CshopUi::shopItemStatInfo()
{
	char grade[100];
	char atk[100];
	char def[100];
	char hp[100];
	char mp[100];
	char cri[100];
	char criAtk[100];
	char speed[100];
	char level[100];

	wsprintf(grade, "��� : %s", m_shop->getShopSelectItem()->getItemGrade().c_str());
	wsprintf(atk, "���ݷ�: %d", m_shop->getShopSelectItem()->getAtk());
	wsprintf(def, "����: %d", m_shop->getShopSelectItem()->getDef());
	wsprintf(hp, "HP: %d", m_shop->getShopSelectItem()->getHp());
	wsprintf(mp, "MP: %d", m_shop->getShopSelectItem()->getMp());
	wsprintf(cri, "ũ����: %d%", m_shop->getShopSelectItem()->getCritical());
	sprintf(criAtk, "ũ�����ݷ�: %.1f", m_shop->getShopSelectItem()->getCriticalAtk());
	sprintf(speed, "�̵��ӵ�: %.1f", m_shop->getShopSelectItem()->getSpeed());
	wsprintf(level, "���ѷ���: %d", m_shop->getShopSelectItem()->getLimitLevel());

	switch (m_shop->getShopSelectItem()->getType())
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 280, level, lstrlen(level));
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 120, grade, lstrlen(grade));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 140, atk, lstrlen(atk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 160, def, lstrlen(def));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 180, hp, lstrlen(hp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 200, mp, lstrlen(mp));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 220, cri, lstrlen(cri));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 240, criAtk, lstrlen(criAtk));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 260, speed, lstrlen(speed));
		TextOut(getMemDC(), m_shopInfo.left + 10, m_shopInfo.top + 280, level, lstrlen(level));
		break;
	default:
		break;
	}
}
