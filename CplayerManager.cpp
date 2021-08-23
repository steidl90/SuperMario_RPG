#include "framework.h"
#include "CplayerManager.h"
#include "CenemyManager.h"
#include "Cmevius.h"
CplayerManager::CplayerManager()
{
}

CplayerManager::~CplayerManager()
{
}


HRESULT CplayerManager::init()
{
    EFFECT->addEffect("히트1", "images/Hit.bmp", 414, 71, 69, 71, 1, 0.2f, 10);

    m_player = new Cplayer;
    m_player->init();

    m_playerUi = new CplayerUi;
    m_playerUi->setPlayerMemoryLink(m_player);
    m_playerUi->init();

    m_inventory = new Cinventory;
    m_inventory->init();

    m_InventoryUI = new CinventoryUi;
    m_InventoryUI->setInventoryMemory(m_inventory);

    m_InventoryUI->setPlayerMemory(m_player);
    m_InventoryUI->init();

    m_dropItem = new CdropItem;
    m_dropItem->init();

    

    isInventoryOn = false;
    return S_OK;
}

void CplayerManager::release()
{
    SAFE_DELETE(m_player);
    SAFE_DELETE(m_playerUi);
    SAFE_DELETE(m_inventory);
    SAFE_DELETE(m_InventoryUI);
    SAFE_DELETE(m_dropItem);
}

void CplayerManager::update()
{
    if (InputManager->isOnceKeyDown('I'))
        isInventoryOn = !isInventoryOn;
    EFFECT->update();
    // nullptr일경우  size연산 접근오류이므로 예외처리
    //if (m_fastLoadLocation != nullptr)
    //{
    //    // 리스트의 사이즈가 1이상이면 플레이어쪽에 에이스타 경로좌표 1번 set해주고 끝, 경로좌표가 초기화될시 다시 set해줄 준비
    //    if (m_fastLoadLocation->size() > 0)
    //    {
    //        if (isAstar)
    //        {
    //            m_player->setIsAstar(true);
    //            m_player->setAstarMove(m_fastLoadLocation);
    //        }
    //        isAstar = false;
    //    }
    //    else
    //        isAstar = true;
    //}
    m_player->update();
    if(isInventoryOn) m_InventoryUI->update();
    m_playerUi->update();

    this->getItem();
    this->usePotion();
}

void CplayerManager::render()
{
    m_dropItem->render();
    m_player->render();
    m_playerUi->render();
    EFFECT->render();
    if (isInventoryOn)
    {
        m_InventoryUI->render();
        this->showPlayerStat();
    }
}

void CplayerManager::showPlayerStat()
{
    vector<Citem*> equipSet;
    if(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item != nullptr) equipSet.push_back(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_WEAPON)->m_item);
    if(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_ARMOR)->m_item != nullptr) equipSet.push_back(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_ARMOR)->m_item);
    if(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_SHOES)->m_item != nullptr) equipSet.push_back(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_SHOES)->m_item);
    if(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_GLOVES)->m_item != nullptr) equipSet.push_back(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_GLOVES)->m_item);
    if(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_PENDANT)->m_item != nullptr) equipSet.push_back(m_inventory->getEquipItem(ITEMTYPE::ITEMTYPE_PENDANT)->m_item);
    //if (m_inventory->getEquipArmor() != nullptr) equipSet.push_back(m_inventory->getEquipArmor());
    //if (m_inventory->getEquipShoes() != nullptr) equipSet.push_back(m_inventory->getEquipShoes());
    //if (m_inventory->getEquipGloves() != nullptr) equipSet.push_back(m_inventory->getEquipGloves());
    //if (m_inventory->getEquipPendant() != nullptr) equipSet.push_back(m_inventory->getEquipPendant());
   
    int itemAtk = 0;
    int itemDef = 0;
    int itemHp = 0;
    int itemMp = 0;
    int itemCri = 0;
    float itemCriAtk = 0;
    float itemSpeed = 0;

    for (auto iter = equipSet.begin(); iter != equipSet.end(); ++iter)
    {
        itemAtk += (*iter)->getAtk();
        itemDef += (*iter)->getDef();
        itemHp += (*iter)->getHp();
        itemMp += (*iter)->getMp();
        itemCri += (*iter)->getCritical();
        itemCriAtk += (*iter)->getCriticalAtk();
        itemSpeed += (*iter)->getSpeed();
    }
    // 인벤토리창 옮길거면 좌표값도 UI것 해줘야한다, 현재는 임시

    TCHAR str[100];
    wsprintf(str, "Atk: %d + %d", m_player->getAtk() - itemAtk, itemAtk);
    TextOut(getMemDC(), WINSIZEX / 2 + 210, 330, str, lstrlen(str));
    wsprintf(str, "Def: %d + %d", m_player->getDef() - itemDef, itemDef);
    TextOut(getMemDC(), WINSIZEX / 2 + 210, 350, str, lstrlen(str));
    wsprintf(str, "Hp: %d + %d", m_player->getHp() - itemHp, itemHp);
    TextOut(getMemDC(), WINSIZEX / 2 + 210, 370, str, lstrlen(str));
    wsprintf(str, "Mp: %d + %d", m_player->getMp() - itemMp, itemMp);
    TextOut(getMemDC(), WINSIZEX / 2 + 210, 390, str, lstrlen(str)); 
    wsprintf(str, "Critical: %d + %d", m_player->getCritical() - itemCri, itemCri);
    TextOut(getMemDC(), WINSIZEX / 2 + 210, 410, str, lstrlen(str));
    sprintf(str, "CriAtk: %.1f + %.1f", m_player->getCriticalAtk() - itemCriAtk, itemCriAtk);
    TextOut(getMemDC(), WINSIZEX / 2 + 210, 430, str, lstrlen(str));
    sprintf(str, "Speed: %.1f + %.1f", m_player->getSpeed() - itemSpeed, itemSpeed);
    TextOut(getMemDC(), WINSIZEX / 2 + 210, 450, str, lstrlen(str));

}

void CplayerManager::collisionEnemy()
{
    RECT temp;
    char atk[100];
    auto iter = m_enemy->getEnemy()->begin();
    int i = 0;

    for (iter; iter != m_enemy->getEnemy()->end(); ++iter, i++)
    {
        if (IntersectRect(&temp, m_player->getPlayerAttackRC(), &(*iter)->getRect()))
        {
            (*iter)->setHp((*iter)->getHp() - ((m_player->getAtk() * 0.5) - (*iter)->getDef()));
            sprintf(atk, "-%.1f", ((m_player->getAtk() * 0.5) - (*iter)->getDef()));
            HFONT font, saveFont;
            font = CreateFont(25, 0, 0, 0, 100, false, false, false, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
            saveFont = (HFONT)SelectObject(getMapDC(), font);
            SetBkMode(getMapDC(), TRANSPARENT);
            SetTextColor(getMapDC(), RGB(255, 0, 0));
            TextOut(getMapDC(), (*iter)->getRect().left + ((*iter)->getRect().right - (*iter)->getRect().left) / 2, (*iter)->getRect().top + 10, atk, lstrlen(atk));
            DeleteObject(SelectObject(getMapDC(), saveFont));
            EFFECT->play("히트1", (*iter)->getRect().left + ((*iter)->getRect().right - (*iter)->getRect().left) / 2 + RND->getFromIntTo(0, 30),
                (*iter)->getRect().top + ((*iter)->getRect().bottom - (*iter)->getRect().top) / 2 + RND->getFromIntTo(0, 30));
            
        }

        if (IntersectRect(&temp, m_player->getPlayerLightningCenterRC(), &(*iter)->getRect()) ||
            IntersectRect(&temp, m_player->getPlayerLightningLeftRC(), &(*iter)->getRect()) || 
            IntersectRect(&temp, m_player->getPlayerLightningUpRC(), &(*iter)->getRect()) || 
            IntersectRect(&temp, m_player->getPlayerLightningRightRC(), &(*iter)->getRect()) || 
            IntersectRect(&temp, m_player->getPlayerLightningDownRC(), &(*iter)->getRect()))
        {
            (*iter)->setHp((*iter)->getHp() - ((m_player->getAtk() * 0.3) - (*iter)->getDef()));
            sprintf(atk, "-%.1f", ((m_player->getAtk()*0.3) - (*iter)->getDef()));
            HFONT font, saveFont;
            font = CreateFont(25, 0, 0, 0, 100, false, false, false, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
            saveFont = (HFONT)SelectObject(getMapDC(), font);
            SetBkMode(getMapDC(), TRANSPARENT);
            SetTextColor(getMapDC(), RGB(255, 0, 0));
            TextOut(getMapDC(), (*iter)->getRect().left + ((*iter)->getRect().right - (*iter)->getRect().left) / 2, (*iter)->getRect().top + 10, atk, lstrlen(atk));
            DeleteObject(SelectObject(getMapDC(), saveFont));
            EFFECT->play("히트1", (*iter)->getRect().left + ((*iter)->getRect().right - (*iter)->getRect().left) / 2 + RND->getFromIntTo(0, 30),
                (*iter)->getRect().top + ((*iter)->getRect().bottom - (*iter)->getRect().top) / 2 + RND->getFromIntTo(0, 30));

        }


        for (int j = 0; j < m_player->getSkill()->getvSkill().size(); j++)
        {
            if (IntersectRect(&temp, &m_player->getSkill()->getvSkill()[j].m_skillRc, &(*iter)->getRect()))
            {
                (*iter)->setHp((*iter)->getHp() - 1);
                //m_player->getSkill()->removeSkill(j);
                sprintf(atk, "-%.1f", 1.0f);
                HFONT font, saveFont;
                font = CreateFont(25, 0, 0, 0, 100, false, false, false, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
                saveFont = (HFONT)SelectObject(getMapDC(), font);
                SetBkMode(getMapDC(), TRANSPARENT);
                SetTextColor(getMapDC(), RGB(255, 0, 0));
                TextOut(getMapDC(), (*iter)->getRect().left + ((*iter)->getRect().right - (*iter)->getRect().left) / 2, (*iter)->getRect().top + 10, atk, lstrlen(atk));
                DeleteObject(SelectObject(getMapDC(), saveFont));
                EFFECT->play("히트1", (*iter)->getRect().left + ((*iter)->getRect().right - (*iter)->getRect().left) / 2 + RND->getFromIntTo(0, 30),
                    (*iter)->getRect().top + ((*iter)->getRect().bottom - (*iter)->getRect().top) / 2 + RND->getFromIntTo(0, 30));
            }
        }

        if ((*iter)->getHp() <= 0)
        {
            m_deathCount++;
            if (m_deathCount % 2 == 0) {
                m_player->setExp(m_player->getExp() + (*iter)->getExp());
                m_dropItem->makeItem((*iter)->getX(), (*iter)->getY());
                m_enemy->removeMinion(i);
                m_quest->setQuest(m_quest->getQuest() + 1);
            }
            break;
        }
    }

    RECT tempBoss;
    if (IntersectRect(&tempBoss, m_player->getPlayerAttackRC(), m_boss->getRect()))
    {
        m_boss->setHp(m_boss->getHp() - (m_player->getAtk() * 0.5));
        sprintf(atk, "-%.1f", m_player->getAtk() * 0.5);
        HFONT font, saveFont;
        font = CreateFont(25, 0, 0, 0, 100, false, false, false, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
        saveFont = (HFONT)SelectObject(getMapDC(), font);
        SetBkMode(getMapDC(), TRANSPARENT);
        SetTextColor(getMapDC(), RGB(255, 0, 0));
        TextOut(getMapDC(), m_boss->getRect()->left + (m_boss->getRect()->right - m_boss->getRect()->left) / 2, m_boss->getRect()->top + 10, atk, lstrlen(atk));
        DeleteObject(SelectObject(getMapDC(), saveFont));
        EFFECT->play("히트1", m_boss->getRect()->left + (m_boss->getRect()->right - m_boss->getRect()->left) / 2 + RND->getFromIntTo(0, 30),
            m_boss->getRect()->top + (m_boss->getRect()->bottom - m_boss->getRect()->top) / 2 + RND->getFromIntTo(0, 30));
    }
    if (IntersectRect(&temp, m_player->getPlayerLightningCenterRC(), m_boss->getRect()) ||
        IntersectRect(&temp, m_player->getPlayerLightningLeftRC(), m_boss->getRect()) ||
        IntersectRect(&temp, m_player->getPlayerLightningUpRC(), m_boss->getRect()) ||
        IntersectRect(&temp, m_player->getPlayerLightningRightRC(), m_boss->getRect()) ||
        IntersectRect(&temp, m_player->getPlayerLightningDownRC(), m_boss->getRect()))
    {
        m_boss->setHp(m_boss->getHp() - (m_player->getAtk() * 0.3));
        sprintf(atk, "-%.1f", m_player->getAtk() * 0.5);
        HFONT font, saveFont;
        font = CreateFont(25, 0, 0, 0, 100, false, false, false, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
        saveFont = (HFONT)SelectObject(getMapDC(), font);
        SetBkMode(getMapDC(), TRANSPARENT);
        SetTextColor(getMapDC(), RGB(255, 0, 0));
        TextOut(getMapDC(), m_boss->getRect()->left + (m_boss->getRect()->right - m_boss->getRect()->left) / 2, m_boss->getRect()->top + 10, atk, lstrlen(atk));
        DeleteObject(SelectObject(getMapDC(), saveFont));
        EFFECT->play("히트1", m_boss->getRect()->left + (m_boss->getRect()->right - m_boss->getRect()->left) / 2 + RND->getFromIntTo(0, 30),
            m_boss->getRect()->top + (m_boss->getRect()->bottom - m_boss->getRect()->top) / 2 + RND->getFromIntTo(0, 30));
    }

    for (int j = 0; j < m_player->getSkill()->getvSkill().size(); j++)
    {
        if (IntersectRect(&tempBoss, &m_player->getSkill()->getvSkill()[j].m_skillRc, m_boss->getRect()))
        {
            m_boss->setHp(m_boss->getHp() - 1);
            sprintf(atk, "-%.1f", 1.0f);
            HFONT font, saveFont;
            font = CreateFont(25, 0, 0, 0, 100, false, false, false, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("휴먼둥근헤드라인"));
            saveFont = (HFONT)SelectObject(getMapDC(), font);
            SetBkMode(getMapDC(), TRANSPARENT);
            SetTextColor(getMapDC(), RGB(255, 0, 0));
            TextOut(getMapDC(), m_boss->getRect()->left + (m_boss->getRect()->right - m_boss->getRect()->left) / 2, m_boss->getRect()->top + 10, atk, lstrlen(atk));
            DeleteObject(SelectObject(getMapDC(), saveFont));
            EFFECT->play("히트1", m_boss->getRect()->left + (m_boss->getRect()->right - m_boss->getRect()->left) / 2 + RND->getFromIntTo(0, 30),
                m_boss->getRect()->top + (m_boss->getRect()->bottom - m_boss->getRect()->top) / 2 + RND->getFromIntTo(0, 30));
        }
    }

    /*if (m_boss->getHp() <= 0)
    {
        PostQuitMessage(0);
    }*/
    
}

void CplayerManager::getItem()
{
    RECT temp;
    for (int i = 0; i < m_dropItem->getDropItemList().size(); i++)
    {
        if (IntersectRect(&temp, m_player->getplayerMoveRC(), &m_dropItem->getDropItemList()[i].itemRect))
        {
            if (InputManager->isOnceKeyDown('Z'))
            {
                m_inventory->addItem(m_dropItem->getDropItemList()[i].item);
                m_dropItem->removeItem(i);
            }
        }
    }
}

void CplayerManager::usePotion()
{
    if (InputManager->isOnceKeyDown('T'))
    {
        if (m_inventory->getPotion()->Count > 0)
        {
            m_inventory->setPotion(m_inventory->getPotion()->Count - 1);
            m_player->setHp(m_player->getHp() + m_inventory->getPotion()->recoveryHp);
            m_player->setMp(m_player->getMp() + m_inventory->getPotion()->recoveryMp);

            if (m_player->getHp() > m_player->getMaxHp())
                m_player->setHp(m_player->getMaxHp());
            if (m_player->getMp() > m_player->getMaxMp())
                m_player->setMp(m_player->getMaxMp());
        }
    }
}
