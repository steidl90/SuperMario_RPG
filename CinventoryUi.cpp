#include "framework.h"
#include "CinventoryUi.h"
#include "Cplayer.h"
CinventoryUi::CinventoryUi()
{
}

CinventoryUi::~CinventoryUi()
{
}

HRESULT CinventoryUi::init()
{
	// ��ü UI ��ǥ
	m_uiX = 200;
	m_uiY = 200;

	m_InventoryRect = RectMake(m_uiX, m_uiY, IMAGE->findImage("�κ��丮3")->getWidth(),
		IMAGE->findImage("�κ��丮3")->getHeight());

	// ���â ���� rect ���� ��ǥ
	m_EquipItemX = m_uiX + 60;
	m_EquipItemY = m_uiY + 70;

	// ������ rect
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			RECT temp;
			temp = RectMake(m_EquipItemX + j * 100, m_EquipItemY + i * 250, 70, 70);
			m_vEquipItemSubRect.push_back(temp);
		}
	}

	// ������ rect
	for (int i = 0; i < 3; i++)
	{
		RECT temp;
		temp = RectMake(m_EquipItemX + i * 100, m_EquipItemY + 110, 70, 107);
		m_vEquipItemMainRect.push_back(temp);
	}

	// ���� ����Ʈ ���� rect ���� ��ǥ
	m_itemListX = m_uiX + 410;
	m_itemListY = m_uiY + 25;

	for (int i = 0; i < 4; i++)
	{
		RECT temp;
		temp = RectMake(m_itemListX, m_itemListY + i * 88, 200, 80);
		m_vItemListRect.push_back(temp);
	}

	// 
	m_itemInfoX = m_uiX + 645;
	m_itemInfoY = m_uiY + 30;

	m_ItemInfoRect = RectMake(m_itemInfoX, m_itemInfoY, 180, 80);

	// ��� ��ư rect ���� ��ǥ
	m_functionButtonX = m_uiX + 430;
	m_functionButtonY = m_uiY + 390;

	m_equipButton = RectMake(m_functionButtonX - 5, m_functionButtonY + 10, 70, 20);
	m_abandonButton = RectMake(m_functionButtonX + 90, m_functionButtonY + 10, 70, 20);

	isKeyUp = false;
	isButtonClick = false;

	m_showIndex = 0;
	m_showEndIndex = 0;
	m_selectType = ITEMTYPE::ITEMTYPE_WEAPON;
	isSelectRender = false;
	m_clickCount = 0;
	m_SelectIndex = 0;

	for (int i = 0; i < 5; i++)
	{
		ZeroMemory(&m_equipItem[i], sizeof(m_equipItem));
	}
	return S_OK;
}

void CinventoryUi::release()
{
}

void CinventoryUi::update()
{

	this->selectPotion();
	if (m_selectType == ITEMTYPE::ITEMTYPE_POTION)
	{
		this->selectItemTypeMain();
		this->selectItemTypeSub();
	}
	else
	{
		this->selectItem();
		this->selectEquipItem();
		this->selectItemTypeMain();
		this->selectItemTypeSub();
		this->abandonItem();
		this->clickEquipButton();
	}

	// ���� �߿� �ε��� ����� ������ ������ �� ������� �Ŀ� �ٷ� ���ֱ�
	if (zDelta > 0)
		m_showIndex--;
	else if (zDelta < 0)
		m_showIndex++;
	this->setShowIndex();

	if (InputManager->isStayKeyDown(VK_LBUTTON)) isButtonClick = true;
	else
	{
		isButtonClick = false;
		isKeyUp = true;
	}

}

void CinventoryUi::render()
{
	IMAGE->findImage("�κ��丮3")->render(getMemDC(), m_uiX, m_uiY);
	
	for (auto iter = m_vItemListRect.begin(); iter != m_vItemListRect.end(); ++iter)
	{
		//Rectangle(getMemDC(), (*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
	}
	for (auto iter = m_vEquipItemSubRect.begin(); iter != m_vEquipItemSubRect.end(); ++iter)
	{
		//Rectangle(getMemDC(), (*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
	}
	for (auto iter = m_vEquipItemMainRect.begin(); iter != m_vEquipItemMainRect.end(); ++iter)
	{
		//Rectangle(getMemDC(), (*iter).left, (*iter).top, (*iter).right, (*iter).bottom);
	}
	//Rectangle(getMemDC(), m_ItemInfoRect.left, m_ItemInfoRect.top, m_ItemInfoRect.right, m_ItemInfoRect.bottom);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	//Rectangle(getMemDC(), m_equipButton.left, m_equipButton.top, m_equipButton.right, m_equipButton.bottom);
	TextOut(getMemDC(), m_equipButton.left, m_equipButton.top, TEXT("����"), lstrlen("����"));
	//Rectangle(getMemDC(), m_abandonButton.left, m_abandonButton.top, m_abandonButton.right, m_abandonButton.bottom);
	TextOut(getMemDC(), m_abandonButton.left, m_abandonButton.top, TEXT("������"), lstrlen("������"));
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	char strGold[100];
	wsprintf(strGold, "�����ݾ�: %dGold", m_player->getGold());
	TextOut(getMemDC(), m_equipButton.left, m_equipButton.top + 30, strGold, lstrlen(strGold));

	// ���õ� Ÿ�Ժ� ������ ���
	this->showListItemType();
	// ���� �׵θ�
	if (m_selectType != ITEMTYPE::ITEMTYPE_POTION)
		this->showEquipSelect();
	else
		this->showPotionInfo();
	// ���ý� ��� �κ�
	if (m_Inventory->getSelectItem()->isSelect)
	{
		IMAGE->findImage("�����׵θ�")->render(getMemDC(), m_selectRenderX, m_selectRenderY);
		this->showItemInfo();
	}
	// ���â ����
	// equipMain��Ʈ - 0,2: ���� / 1:����, equipSub��Ʈ - 0: �Ҵ�Ʈ, 3:�尩, 4:�Ź�

	if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->isEquip)
	{
		IMAGE->findImage(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item->getBigImage())->frameRender(getMemDC(),
			m_vEquipItemMainRect[0].left - 10, m_vEquipItemMainRect[0].top + 10
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item->getFrame().x
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item->getFrame().y);
		IMAGE->findImage(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item->getBigImage())->frameRender(getMemDC(),
			m_vEquipItemMainRect[2].left - 10, m_vEquipItemMainRect[2].top + 10
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item->getFrame().x
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item->getFrame().y);
	}
	if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_ARMOR)->isEquip)
	{
		IMAGE->findImage(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_ARMOR)->m_item->getBigImage())->frameRender(getMemDC(),
			m_vEquipItemMainRect[1].left - 10, m_vEquipItemMainRect[1].top + 10
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_ARMOR)->m_item->getFrame().x
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_ARMOR)->m_item->getFrame().y);
	}
	if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_SHOES)->isEquip)
	{
		IMAGE->findImage(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_SHOES)->m_item->getBigImage())->frameRender(getMemDC(),
			m_vEquipItemSubRect[4].left - 10, m_vEquipItemSubRect[4].top + 10
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_SHOES)->m_item->getFrame().x
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_SHOES)->m_item->getFrame().y);
	}
	if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_GLOVES)->isEquip)
	{
		IMAGE->findImage(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_GLOVES)->m_item->getBigImage())->frameRender(getMemDC(),
			m_vEquipItemSubRect[3].left - 10, m_vEquipItemSubRect[3].top + 10
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_GLOVES)->m_item->getFrame().x
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_GLOVES)->m_item->getFrame().y);
	}
	if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_PENDANT)->isEquip)
	{
		IMAGE->findImage(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_PENDANT)->m_item->getBigImage())->frameRender(getMemDC(),
			m_vEquipItemSubRect[0].left - 10, m_vEquipItemSubRect[0].top + 10
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_PENDANT)->m_item->getFrame().x
			, m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_PENDANT)->m_item->getFrame().y);
	}
}

// ���� ����ó�� �ϼ� �ȵ�.. ��ũ�� ������ �������� ����ó�� �ʿ�
// ��ũ�� ����� ������, �κ��丮 ����Ʈ�� ������ 4�� �ε��� ����
// ��� Ÿ�Ժ� showIndex �ʿ��ҵ�?
void CinventoryUi::setShowIndex()
{
	switch (m_selectType)
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		if (m_Inventory->getvWeaponList()->size() < 5)
		{
			m_showIndex = 0;
			m_showEndIndex = m_Inventory->getvWeaponList()->size();
		}
		else if (m_showIndex < 0)
		{
			m_showIndex = 0;
			m_showEndIndex = m_showIndex + 4;
		}
		else if (m_Inventory->getvWeaponList()->size() - 4 < m_showIndex)	// ������ ��ũ������ ��
		{
			m_showIndex = m_Inventory->getvWeaponList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;

		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		if (m_Inventory->getvArmorList()->size() < 5)
		{
			m_showIndex = 0;
			m_showEndIndex = m_Inventory->getvArmorList()->size();
		}
		else if (m_showIndex < 0)
		{
			m_showIndex = 0;
			m_showEndIndex = m_showIndex + 4;
		}
		else if (m_Inventory->getvArmorList()->size() - 4 < m_showIndex)	// ������ ��ũ������ �� ����ó��
		{
			m_showIndex = m_Inventory->getvArmorList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;

		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		if (m_Inventory->getvShoesList()->size() < 5)
		{
			m_showIndex = 0;
			m_showEndIndex = m_Inventory->getvShoesList()->size();
		}
		else if (m_showIndex < 0)
		{
			m_showIndex = 0;
			m_showEndIndex = m_showIndex + 4;
		}
		else if (m_Inventory->getvShoesList()->size() - 4 < m_showIndex)	// ������ ��ũ������ ��
		{
			m_showIndex = m_Inventory->getvShoesList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;

		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		if (m_Inventory->getvGlovesList()->size() < 5)
		{
			m_showIndex = 0;
			m_showEndIndex = m_Inventory->getvGlovesList()->size();
		}
		else if (m_showIndex < 0)
		{
			m_showIndex = 0;
			m_showEndIndex = m_showIndex + 4;
		}
		else if (m_Inventory->getvGlovesList()->size() - 4 < m_showIndex)	// ������ ��ũ������ ��
		{
			m_showIndex = m_Inventory->getvGlovesList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		if (m_Inventory->getvPendantList()->size() < 5)
		{
			m_showIndex = 0;
			m_showEndIndex = m_Inventory->getvPendantList()->size();
		}
		else if (m_showIndex < 0)
		{
			m_showIndex = 0;
			m_showEndIndex = m_showIndex + 4;
		}
		else if (m_Inventory->getvPendantList()->size() - 4 < m_showIndex)	// ������ ��ũ������ ��
		{
			m_showIndex = m_Inventory->getvPendantList()->size() - 4;
			m_showEndIndex = m_showIndex + 4;
		}
		else m_showEndIndex = m_showIndex + 4;
		
		break;
	default:
		break;
	}
}

// ������ Ÿ���� ������ Ÿ�Ը� �κ��丮 ����Ʈ�� ������
void CinventoryUi::showListItemType()
{
	switch (m_selectType)
	{
	case ITEMTYPE::ITEMTYPE_WEAPON:
		showItemList(m_Inventory->getvWeaponList());
		break;
	case ITEMTYPE::ITEMTYPE_ARMOR:
		showItemList(m_Inventory->getvArmorList());
		break;
	case ITEMTYPE::ITEMTYPE_GLOVES:
		showItemList(m_Inventory->getvGlovesList());
		break;
	case ITEMTYPE::ITEMTYPE_SHOES:
		showItemList(m_Inventory->getvShoesList());
		break;
	case ITEMTYPE::ITEMTYPE_PENDANT:
		showItemList(m_Inventory->getvPendantList());
		break;
	default:
		break;
	}
}
// �ε��� �������� ���͸� �����Ͽ�
void CinventoryUi::showItemList(vector<Citem*>* list)
{
	char str[100];
	// show �ε����� �����ε����� �����ϸ� �ű���� ������ ������ �����ִ� ���� (�ִ� 4��)
	// j �ε����� ��Ʈ 0~3���� �����ϱ� ���� �ε���
	// i �ε����� show�ε����� �븮 ����(showIndex���� ���ϸ� �ȵǴ�)
	int	i = m_showIndex;
	int j = 0;
	vector<Citem*>::iterator iter;
	for ( iter = list->begin() + i; i < m_showEndIndex; ++iter, i++, j++)
	{
		IMAGE->findImage((*iter)->getSmallImage())->frameRender(getMemDC()
			,m_vItemListRect[j].left, m_vItemListRect[j].top, (*iter)->getFrame().x, (*iter)->getFrame().y);

		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), m_vItemListRect[j].left + 80, m_vItemListRect[j].top + 10, (*iter)->getName().c_str(), lstrlen((*iter)->getName().c_str()));
		wsprintf(str, "�ʿ� ����: %d", (*iter)->getLimitLevel());
		TextOut(getMemDC(), m_vItemListRect[j].left + 80, m_vItemListRect[j].top + 30, str, lstrlen(str));
		wsprintf(str, "���: %d", (*iter)->getBuyPrice());
		TextOut(getMemDC(), m_vItemListRect[j].left + 80, m_vItemListRect[j].top + 50, str, lstrlen(str));
	}
}

// ���� �ε����� ����ؼ� ���� ������ �׵θ� ��ġ ����
// ���� �Ϸ�
void CinventoryUi::showEquipSelect()
{
	int renderIndex;
	bool isEquipSelectRender = true;
	//renderIndex = m_equipItem[static_cast<int>(m_selectType)].m_itemIndex - m_showIndex;
	renderIndex = m_Inventory->getEquipItem(m_selectType)->m_itemIndex - m_showIndex;
	if (renderIndex < 0 || renderIndex > 3)
		isEquipSelectRender = false;
	for (int i = 0; i < 4; i++)
	{
		if (i == renderIndex)
		{
			m_equipRenderX = m_vItemListRect[i].left - 5;
			m_equipRenderY = m_vItemListRect[i].top - 3;
			m_Inventory->setEquipRender(m_selectType, PointMake(m_equipRenderX, m_equipRenderY));
		}
	}

	if (isEquipSelectRender)
	{
		if ( m_Inventory->getEquipItem(m_selectType)->isEquip )
			IMAGE->findImage("�����׵θ�")->render(getMemDC(), m_Inventory->getEquipItem(m_selectType)->m_renderPoint.x,
				m_Inventory->getEquipItem(m_selectType)->m_renderPoint.y);
	}
}

// ���콺 1Ŭ������ ������ ����ǥ��
// ���� �Ϸ�
void CinventoryUi::selectItem()
{
	int i = m_showIndex;
	vector<Citem*>::iterator itemIter;
	for (auto iter = m_vItemListRect.begin(); i < m_showEndIndex; ++iter, i++)
	{
		if (PtInRect(&(*iter), m_ptMouse))
		{
			if (InputManager->isOnceKeyDown(VK_LBUTTON))
			{
				// ������ ������ ���� inventory ���� �����ͼ� selectItem ������ ���
				m_selectRenderX = (*iter).left - 5;
				m_selectRenderY = (*iter).top - 3;
				switch (m_selectType)
				{
				case ITEMTYPE::ITEMTYPE_WEAPON:
					itemIter = m_Inventory->getvWeaponList()->begin() + i;
					break;
				case ITEMTYPE::ITEMTYPE_ARMOR:
					itemIter = m_Inventory->getvArmorList()->begin() + i;
					break;
				case ITEMTYPE::ITEMTYPE_GLOVES:
					itemIter = m_Inventory->getvGlovesList()->begin() + i;
					break;
				case ITEMTYPE::ITEMTYPE_SHOES:
					itemIter = m_Inventory->getvShoesList()->begin() + i;
					break;
				case ITEMTYPE::ITEMTYPE_PENDANT:
					itemIter = m_Inventory->getvPendantList()->begin() + i;
					break;
				}
				m_Inventory->setSelectItem((*itemIter), i
					, PointMake(m_selectRenderX, m_selectRenderY), true);
			}
		}
	}
}
// ���콺 2Ŭ������ ������ ����ǥ�� / ����
// ���� �Ϸ�
void CinventoryUi::selectEquipItem()
{
	int i = m_showIndex;
	vector<RECT>::iterator iter;
	for (iter = m_vItemListRect.begin(); i < m_showEndIndex; ++iter, i++)
	{
		if (PtInRect(&(*iter), m_ptMouse))
		{
			// ���� ��Ʈ Ŭ���ϰ��ִ��� üũ
			if (m_clickCheckRect.top != (*iter).top)
				m_clickCount = 0;
			m_clickCheckRect = (*iter);
			
			if (InputManager->isStayKeyDown(VK_LBUTTON))
			{
				isButtonClick = true;
				if (isButtonClick)
				{
					if (isKeyUp)
					{
						if (m_clickCount == 0)
							m_compareTime = TIME->getWorldTime();
						m_clickCount++;

						// ���콺 ����Ŭ�� �Ǵ� ����!
						// ������ ������ ���� ��� �� ����
						if (m_clickCount > 1)
						{
							if (m_Inventory->getSelectItem()->m_item != nullptr)
							{
								if (m_Inventory->getSelectItem()->m_item->getLimitLevel() <= m_player->getLv())
								{
									this->setPlayerStat(i);
									m_Inventory->equipItem();
								}
							}
						}
						isKeyUp = false;
					}
				}
			}
			else
			{
				isButtonClick = false;
				isKeyUp = true;
			}
		}
	}
	if (m_compareTime + 1 < TIME->getWorldTime())
		m_clickCount = 0;
}
// ������ ����!
// ������ ������ ����ü�迭 �� ������ ������ ���� �־��ֱ�
// ���� �Ϸ�
//void CinventoryUi::setEquipItem(int index, int x, int y)
//{
//
//			//this->setPlayerStat(index);
//			//m_Inventory->equipItem();
//}

// ���� �Ϸ�
void CinventoryUi::setPlayerStat(int index)
{
	Citem* Temp[5];

	// ������ ������ Ÿ�Կ� ���� �ش� �ε����� ������ ���� �Է�
	Temp[static_cast<int>(m_Inventory->getSelectItem()->m_item->getType())] 
		= m_Inventory->getSelectItem()->m_item;
	for (int i = 0; i < 5; i++)
	{
		if (i == static_cast<int>(m_Inventory->getSelectItem()->m_item->getType()))
		{
			if (m_Inventory->getEquipItem()[i].m_item == nullptr)
			{
				m_player->setAtk(m_player->getAtk() + Temp[i]->getAtk());
				m_player->setDef(m_player->getDef() + Temp[i]->getDef());
				m_player->setMaxHp(m_player->getMaxHp() + Temp[i]->getHp());
				m_player->setMaxMp(m_player->getMaxMp() + Temp[i]->getMp());
				m_player->setCritical(m_player->getCritical() + Temp[i]->getCritical());
				m_player->setCriticalAtk(m_player->getCriticalAtk() + Temp[i]->getCriticalAtk());
				m_player->setSpeed(m_player->getSpeed() + Temp[i]->getSpeed());
			}
			else
			{	// �̹� ������ ������ �ɷ�ġ ����
				m_player->setAtk(m_player->getAtk() - m_Inventory->getEquipItem()[i].m_item->getAtk());
				m_player->setDef(m_player->getDef() - m_Inventory->getEquipItem()[i].m_item->getDef());
				m_player->setMaxHp(m_player->getMaxHp() - m_Inventory->getEquipItem()[i].m_item->getHp());
				m_player->setMaxMp(m_player->getMaxMp() - m_Inventory->getEquipItem()[i].m_item->getMp());
				m_player->setCritical(m_player->getCritical() - m_Inventory->getEquipItem()[i].m_item->getCritical());
				m_player->setCriticalAtk(m_player->getCriticalAtk() - m_Inventory->getEquipItem()[i].m_item->getCriticalAtk());
				m_player->setSpeed(m_player->getSpeed() - m_Inventory->getEquipItem()[i].m_item->getSpeed());

				m_player->setAtk(m_player->getAtk() + Temp[i]->getAtk());
				m_player->setDef(m_player->getDef() + Temp[i]->getDef());
				m_player->setMaxHp(m_player->getMaxHp() + Temp[i]->getHp());
				m_player->setMaxMp(m_player->getMaxMp() + Temp[i]->getMp());
				m_player->setCritical(m_player->getCritical() + Temp[i]->getCritical());
				m_player->setCriticalAtk(m_player->getCriticalAtk() + Temp[i]->getCriticalAtk());
				m_player->setSpeed(m_player->getSpeed() + Temp[i]->getSpeed());
			}
		}
	}
}

// ���� �Ϸ�
void CinventoryUi::clickEquipButton()
{
	if (PtInRect(&m_equipButton, m_ptMouse))
	{
		if (isButtonClick)
		{
			if (isKeyUp)
			{
				if (m_Inventory->getSelectItem()->m_item != nullptr)
				{
					if (m_Inventory->getSelectItem()->m_item->getLimitLevel() <= m_player->getLv())
					{
						this->setPlayerStat(m_Inventory->getSelectItem()->m_itemIndex);
						m_Inventory->equipItem();
						isKeyUp = false;
					}
				}
			}
		}
	}
}

// ���â ������ĭ Ŭ���� �۵��Ǵ� �͵�
// ���� �Ϸ�
void CinventoryUi::selectItemTypeMain()
{
	vector<RECT>::iterator iter;
	for ( iter = m_vEquipItemMainRect.begin(); iter != m_vEquipItemMainRect.end(); ++iter)
	{
		if (PtInRect(&(*iter), m_ptMouse))
		{
			// ���� ��Ʈ Ŭ���ϰ��ִ��� üũ
			if (m_clickCheckRect.left != (*iter).left)
				m_clickCount = 0;
			m_clickCheckRect = (*iter);
			if (isButtonClick)
			{
				if (isKeyUp)
				{
					if (m_clickCount == 0)
						m_compareTime = TIME->getWorldTime();
					m_clickCount++;

					// Ŭ���� ���â rect�ε����� ���� Ÿ�Լ��� 1: ���� 0,2: ����
					if ((*iter).left == m_vEquipItemMainRect[1].left)
					{
						m_selectType = ITEMTYPE::ITEMTYPE_ARMOR;
					}
					else
						m_selectType = ITEMTYPE::ITEMTYPE_WEAPON;

					m_Inventory->clearSelectItem();
					isSelectRender = false;

					// ���콺 ����Ŭ�� �Ǵ� ����!
					// ���� ����
					if (m_clickCount > 1)
					{
						if ((*iter).left == m_vEquipItemMainRect[1].left)
						{
							if(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_ARMOR)->m_item != nullptr)
								this->unEquipItem();
						}
						else
						{
							if(m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item != nullptr)
								this->unEquipItem();
						}
					}
					isKeyUp = false;
				}
			}
		}
	}

	if (m_compareTime + 1 < TIME->getWorldTime())
		m_clickCount = 0;
}

// �ֺ� ���� ���â ĭ Ŭ����
// ���� �Ϸ�
void CinventoryUi::selectItemTypeSub()
{
	vector<RECT>::iterator iter;
	for (iter = m_vEquipItemSubRect.begin(); iter != m_vEquipItemSubRect.end(); ++iter)
	{
		if (PtInRect(&(*iter), m_ptMouse))
		{
			// ���� ��Ʈ Ŭ���ϰ��ִ��� üũ
			if (m_clickCheckRect.left != (*iter).left)
				m_clickCount = 0;
			m_clickCheckRect = (*iter);
			if (isButtonClick)
			{
				if (isKeyUp)
				{
					if (m_clickCount == 0) 
						m_compareTime = TIME->getWorldTime();
					m_clickCount++;

					// ���̵� üũ�ؾ�
					if ((*iter).left == m_vEquipItemSubRect[0].left && (*iter).top == m_vEquipItemSubRect[0].top)
						m_selectType = ITEMTYPE::ITEMTYPE_PENDANT;
					else if ((*iter).left == m_vEquipItemSubRect[3].left && (*iter).top == m_vEquipItemSubRect[3].top)
						m_selectType = ITEMTYPE::ITEMTYPE_GLOVES;
					else if ((*iter).left == m_vEquipItemSubRect[4].left && (*iter).top == m_vEquipItemSubRect[4].top)
						m_selectType = ITEMTYPE::ITEMTYPE_SHOES;

					m_Inventory->clearSelectItem();
					isSelectRender = false;

					// ���콺 ����Ŭ�� �Ǵ� ����!
					// ���� ����
					// 0: �Ҵ�Ʈ, 3: �尩, 4: �Ź�
					if (m_clickCount > 1)
					{
						if ((*iter).left == m_vEquipItemSubRect[0].left && (*iter).top == m_vEquipItemSubRect[0].top) // 0: �Ҵ�Ʈ
						{
							if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_PENDANT)->m_item != nullptr)
								this->unEquipItem();
						}
						else if ((*iter).left == m_vEquipItemSubRect[3].left && (*iter).top == m_vEquipItemSubRect[3].top) // �尩
						{
							if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_GLOVES)->m_item != nullptr)
								this->unEquipItem();
						}
						else if ((*iter).left == m_vEquipItemSubRect[4].left && (*iter).top == m_vEquipItemSubRect[4].top) // �Ź�
						{
							if (m_Inventory->getEquipItem(ITEMTYPE::ITEMTYPE_SHOES)->m_item != nullptr)
								this->unEquipItem();
						}
					}
					isKeyUp = false;
				}
			}
		}
	}
	if (m_compareTime + 1 < TIME->getWorldTime())
		m_clickCount = 0;
}

// ���� �Ϸ�
void CinventoryUi::showItemInfo()
{
	char str[100];

	IMAGE->findImage(m_Inventory->getSelectItem()->m_item->getSmallImage())->frameRender(getMemDC(), m_ItemInfoRect.left + 11, m_ItemInfoRect.top
		, m_Inventory->getSelectItem()->m_item->getFrame().x
		,m_Inventory->getSelectItem()->m_item->getFrame().y);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 10
		,m_Inventory->getSelectItem()->m_item->getName().c_str()
		,lstrlen(m_Inventory->getSelectItem()->m_item->getName().c_str()));
	wsprintf(str, "�ʿ� ����: %d", m_Inventory->getSelectItem()->m_item->getLimitLevel());
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 30, str, lstrlen(str));
	wsprintf(str, "���: %d", m_Inventory->getSelectItem()->m_item->getBuyPrice());
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 50, str, lstrlen(str));

	this->showItemCompare();

}

//���� �Ϸ�
void CinventoryUi::showItemCompare()
{
	char atk[100];
	char def[100];
	char hp[100];
	char mp[100];
	char cri[100];
	char criAtk[100];
	char speed[100];

	int temp_atk, temp_def, temp_hp, temp_mp, temp_cri;
	float temp_criAtk, temp_speed;


	if (m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item == nullptr)
	{
		temp_atk = temp_def = temp_hp = temp_mp = temp_cri = 0;
		temp_criAtk = temp_speed = 0;
	}
	else
	{
		temp_atk = m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item->getAtk();
		temp_def = m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item->getDef();
		temp_hp = m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item->getHp();
		temp_mp = m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item->getMp();
		temp_cri = m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item->getCritical();
		temp_criAtk = m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item->getCriticalAtk();
		temp_speed = m_Inventory->getEquipItem()[static_cast<int>(m_selectType)].m_item->getSpeed();
	}

	if (m_Inventory->getSelectItem()->m_item->getAtk() - temp_atk > 0)
		wsprintf(atk, "+%d", (m_Inventory->getSelectItem()->m_item->getAtk() - temp_atk));
	else
		wsprintf(atk, "%d", (m_Inventory->getSelectItem()->m_item->getAtk() - temp_atk));
	if (m_Inventory->getSelectItem()->m_item->getDef() - temp_def > 0)
		wsprintf(def, "+%d", (m_Inventory->getSelectItem()->m_item->getDef() - temp_def));
	else
		wsprintf(def, "%d", (m_Inventory->getSelectItem()->m_item->getDef() - temp_def));
	if (m_Inventory->getSelectItem()->m_item->getHp() - temp_hp > 0)
		wsprintf(hp, "+%d", (m_Inventory->getSelectItem()->m_item->getHp() - temp_hp));
	else
		wsprintf(hp, "%d", (m_Inventory->getSelectItem()->m_item->getHp() - temp_hp));
	if (m_Inventory->getSelectItem()->m_item->getMp() - temp_mp > 0)
		wsprintf(mp, "+%d", (m_Inventory->getSelectItem()->m_item->getMp() - temp_mp));
	else
		wsprintf(mp, "%d", (m_Inventory->getSelectItem()->m_item->getMp() - temp_mp));
	if (m_Inventory->getSelectItem()->m_item->getCritical() - temp_cri > 0)
		wsprintf(cri, "+%d", (m_Inventory->getSelectItem()->m_item->getCritical() - temp_cri));
	else
		wsprintf(cri, "%d", (m_Inventory->getSelectItem()->m_item->getCritical() - temp_cri));
	if (m_Inventory->getSelectItem()->m_item->getCriticalAtk() - temp_criAtk > 0)
		sprintf(criAtk, "+%.1f", m_Inventory->getSelectItem()->m_item->getCriticalAtk() - temp_criAtk);
	else
		sprintf(criAtk, "%.1f", m_Inventory->getSelectItem()->m_item->getCriticalAtk() - temp_criAtk);
	if (m_Inventory->getSelectItem()->m_item->getSpeed() - temp_speed > 0)
		sprintf(speed, "+%.1f", m_Inventory->getSelectItem()->m_item->getSpeed() - temp_speed);
	else
		sprintf(speed, "%.1f", m_Inventory->getSelectItem()->m_item->getSpeed() - temp_speed);

	TextOut(getMemDC(), m_ItemInfoRect.left + 140, m_ItemInfoRect.top + 100, atk, lstrlen(atk));
	TextOut(getMemDC(), m_ItemInfoRect.left + 140, m_ItemInfoRect.top + 120, def, lstrlen(def));
	TextOut(getMemDC(), m_ItemInfoRect.left + 140, m_ItemInfoRect.top + 140, hp, lstrlen(hp));
	TextOut(getMemDC(), m_ItemInfoRect.left + 140, m_ItemInfoRect.top + 160, mp, lstrlen(mp));
	TextOut(getMemDC(), m_ItemInfoRect.left + 140, m_ItemInfoRect.top + 180, cri, lstrlen(cri));
	TextOut(getMemDC(), m_ItemInfoRect.left + 140, m_ItemInfoRect.top + 200, criAtk, lstrlen(criAtk));
	TextOut(getMemDC(), m_ItemInfoRect.left + 140, m_ItemInfoRect.top + 220, speed, lstrlen(speed));

}

void CinventoryUi::abandonItem()
{
	if (PtInRect(&m_abandonButton, m_ptMouse))
	{

		if (isButtonClick)
		{
			if (isKeyUp)
			{
				// ���� �������� �������� ����
				// ���������� ���� �����۸� ����

				m_Inventory->AbandonItem();
				m_Inventory->clearSelectItem();
				isKeyUp = false;
			}
		}
	}
}

// �����Ϸ�
void CinventoryUi::unEquipItem()
{

	m_player->setAtk(m_player->getAtk() - m_Inventory->getEquipItem(m_selectType)->m_item->getAtk());
	m_player->setDef(m_player->getDef() - m_Inventory->getEquipItem(m_selectType)->m_item->getDef());
	m_player->setMaxHp(m_player->getMaxHp() - m_Inventory->getEquipItem(m_selectType)->m_item->getHp());
	m_player->setMaxMp(m_player->getMaxMp() - m_Inventory->getEquipItem(m_selectType)->m_item->getMp());
	m_player->setCritical(m_player->getCritical() - m_Inventory->getEquipItem(m_selectType)->m_item->getCritical());
	m_player->setCriticalAtk(m_player->getCriticalAtk() - m_Inventory->getEquipItem(m_selectType)->m_item->getCriticalAtk());
	m_player->setSpeed(m_player->getSpeed() - m_Inventory->getEquipItem(m_selectType)->m_item->getSpeed());

	m_Inventory->clearEquipItem(m_selectType);
}

void CinventoryUi::selectPotion()
{

	if (PtInRect(&m_vEquipItemSubRect[5], m_ptMouse))
	{
		if (isButtonClick)
		{
			if (isKeyUp)
			{
				m_selectType = ITEMTYPE::ITEMTYPE_POTION;
				m_Inventory->clearSelectItem();
				isSelectRender = false;

				isKeyUp = false;
			}
		}
	}
}

void CinventoryUi::showPotionInfo()
{
	char str[100];
	// ���� �̹��� ���ϱ�
	//IMAGE->findImage(m_Inventory->getSelectItem()->m_item->getSmallImage())->frameRender(getMemDC(), m_ItemInfoRect.left + 11, m_ItemInfoRect.top
	//	, m_Inventory->getSelectItem()->m_item->getFrame().x
	//	, m_Inventory->getSelectItem()->m_item->getFrame().y);

	SetTextColor(getMemDC(), RGB(255, 255, 255));
	/*TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 10
		, TEXT("����"), lstrlen("����"));*/
	wsprintf(str, "���� ����: %d", m_Inventory->getPotion()->Count);
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 10, str, lstrlen(str));
	wsprintf(str, "HP ȸ����: %d", m_Inventory->getPotion()->recoveryHp);
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 30, str, lstrlen(str));
	wsprintf(str, "MP ȸ����: %d", m_Inventory->getPotion()->recoveryMp);
	TextOut(getMemDC(), m_ItemInfoRect.left + 80, m_ItemInfoRect.top + 50, str, lstrlen(str));
}
