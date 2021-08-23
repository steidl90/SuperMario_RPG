#include "framework.h"
#include "CNPC.h"

HRESULT CNPC::init()
{
    m_isAni = true;
    //가노르
    m_garNorImage = IMAGE->findImage("NPC가노르");
    ANIMATION->addDefAnimation("가노르", "NPC가노르", 8, false, true);
    m_garNorAni = ANIMATION->findAnimation("가노르");
    m_garNorX = 1000;
    m_garNorY = 550;
    
    //샵키퍼
    m_shopKeeperImage = IMAGE->findImage("NPC샵키퍼");
    ANIMATION->addDefAnimation("샵키퍼", "NPC샵키퍼",10, false, true);
    m_shopKeeperAni = ANIMATION->findAnimation("샵키퍼");
    m_shopKeeperX = 470;
    m_shopKeeperY = 580;

    //블랙마켓
    m_blackMarketImage = IMAGE->findImage("NPC블랙마켓");
    ANIMATION->addDefAnimation("블랙마켓", "NPC블랙마켓",10, false, true);
    m_blackMarketAni = ANIMATION->findAnimation("블랙마켓");
    m_blackMarketX = 1300;
    m_blackMarketY = 710;

    //에드워드
    m_edwardImage = IMAGE->findImage("NPC에드워드");
    ANIMATION->addDefAnimation("에드워드", "NPC에드워드", 5, false, true);
    m_edwardAni = ANIMATION->findAnimation("에드워드");
    m_edwardX = 685;
    m_edwardY = 550;

    //에릭
    m_ericImage = IMAGE->findImage("NPC에릭");
    ANIMATION->addDefAnimation("에릭", "NPC에릭", 10, false, true);
    m_ericAni = ANIMATION->findAnimation("에릭");
    m_ericX = 328;
    m_ericY = 230;

    //할스테인
    m_halsteinImage = IMAGE->findImage("NPC할스테인");
    ANIMATION->addDefAnimation("할스테인", "NPC할스테인", 10, false, true);
    m_halsteinAni = ANIMATION->findAnimation("할스테인");
    m_halsteinX = 1500;
    m_halsteinY = 530;
   
    //카일리아
    m_kaylaImage=IMAGE->findImage("NPC카일리아");
    ANIMATION->addDefAnimation("카일리아", "NPC카일리아", 10, false, true);
    m_kaylaAni = ANIMATION->findAnimation("카일리아");
    m_kaylaX = 435;
    m_kaylaY = 1130;

    //사캐스터
    m_sarcasterImage = IMAGE->findImage("NPC사캐스터");
    ANIMATION->addDefAnimation("사캐스터", "NPC사캐스터", 8, false, true);
    m_sarcasterAni = ANIMATION->findAnimation("사캐스터");
    m_sarcasterX = 220;
    m_sarcasterY = 1500;

    //토스테인
    m_torsteinImage = IMAGE->findImage("NPC토스테인");
    ANIMATION->addDefAnimation("토스테인", "NPC토스테인", 10, false, true);
    m_torsteinAni = ANIMATION->findAnimation("토스테인");
    m_torsteinX = 1170;
    m_torsteinY = 1380;

    //위치
    m_witchImage = IMAGE->findImage("NPC위치");
    ANIMATION->addDefAnimation("위치", "NPC위치", 10, false, true);
    m_witchAni = ANIMATION->findAnimation("위치");
    m_witchX = 540;
    m_witchY = 240;

    //힐링십자가
    IMAGE->findImage("힐링십자가");
    ANIMATION->addDefAnimation("힐링십자가", "힐링십자가", 10, false, true);
    m_healingcrossAni = ANIMATION->findAnimation("힐링십자가");

    return S_OK;
}

void CNPC::release()
{
}

void CNPC::update()
{
    m_garNorRc = RectMake(m_garNorX-25, m_garNorY, m_garNorImage->getFrameWidth()+50, m_garNorImage->getFrameHeight()+50);
    m_shopKeeperRc = RectMake(m_shopKeeperX, m_shopKeeperY, m_shopKeeperImage->getFrameWidth(), m_shopKeeperImage->getFrameHeight());
    m_blackMarketRc = RectMake(m_blackMarketX, m_blackMarketY, m_blackMarketImage->getFrameWidth(), m_blackMarketImage->getFrameHeight());
    m_edwardRc = RectMake(m_edwardX, m_edwardY, m_edwardImage->getFrameWidth(), m_edwardImage->getFrameHeight());
    m_ericRc = RectMake(m_ericX, m_ericY, m_ericImage->getFrameWidth(), m_ericImage->getFrameHeight());
    m_halsteinRc = RectMake(m_halsteinX, m_halsteinY, m_halsteinImage->getFrameWidth(), m_halsteinImage->getFrameHeight());
    m_kaylaRc = RectMake(m_kaylaX, m_kaylaY, m_kaylaImage->getFrameWidth(), m_kaylaImage->getFrameHeight());
    m_sarcasterRc = RectMake(m_sarcasterX, m_sarcasterY, m_sarcasterImage->getFrameWidth(), m_sarcasterImage->getFrameHeight());
    m_torsteinRc = RectMake(m_torsteinX, m_torsteinY, m_torsteinImage->getFrameWidth(), m_torsteinImage->getFrameHeight());
    m_witchRc = RectMake(m_witchX, m_witchY, m_witchImage->getFrameWidth(), m_witchImage->getFrameHeight());
}

void CNPC::render()
{
    if(InputManager->isToggleKey(VK_F1)) getNpcRectangle();
     
    //가노르
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_garNorX + 9, m_garNorY + 37, 100);
    m_garNorImage->aniRender(getMapDC(), m_garNorX, m_garNorY, m_garNorAni);
    //샵키퍼
    IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), m_shopKeeperX - 3, m_shopKeeperY + 40, 100);
    m_shopKeeperImage->aniRender(getMapDC(), m_shopKeeperX, m_shopKeeperY, m_shopKeeperAni);
    //블랙마켓
    m_blackMarketImage->aniRender(getMapDC(), m_blackMarketX, m_blackMarketY, m_blackMarketAni);
    //에드워드
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_edwardX + 3, m_edwardY + 40, 100);
    m_edwardImage->aniRender(getMapDC(), m_edwardX, m_edwardY, m_edwardAni);
    //에릭
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_ericX - 3, m_ericY + 37, 100);
    m_ericImage->aniRender(getMapDC(), m_ericX, m_ericY, m_ericAni);
    //할스테인
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_halsteinX - 1, m_halsteinY + 55, 100);
    m_halsteinImage->aniRender(getMapDC(), m_halsteinX, m_halsteinY, m_halsteinAni);
    //카일리아
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_kaylaX - 3, m_kaylaY + 33, 100);
    m_kaylaImage->aniRender(getMapDC(), m_kaylaX, m_kaylaY, m_kaylaAni);
    IMAGE->findImage("힐링십자가")->aniRender(getMapDC(), m_kaylaX-40, m_kaylaY, m_healingcrossAni);

    //사캐스터
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_sarcasterX-1, m_sarcasterY + 37, 100);
    m_sarcasterImage->aniRender(getMapDC(), m_sarcasterX, m_sarcasterY, m_sarcasterAni);
    //토스테인
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_torsteinX + 8, m_torsteinY + 25, 100);
    m_torsteinImage->aniRender(getMapDC(), m_torsteinX, m_torsteinY, m_torsteinAni);
    //위치
    IMAGE->findImage("NPC그림자")->alphaRender(getMapDC(), m_witchX + 1, m_witchY + 50, 100);
    m_witchImage->aniRender(getMapDC(), m_witchX, m_witchY, m_witchAni);
    

    if (m_isAni)
    {
        getNpcAni();
        m_isAni = false;
    }
}

void CNPC::getNpcAni()
{
    ANIMATION->start("가노르");
    ANIMATION->start("샵키퍼");
    ANIMATION->start("블랙마켓");
    ANIMATION->start("에드워드");
    ANIMATION->start("에릭");
    ANIMATION->start("할스테인");
    ANIMATION->start("카일리아");
    ANIMATION->start("사캐스터");
    ANIMATION->start("토스테인");
    ANIMATION->start("위치");
    ANIMATION->start("힐링십자가");
}

void CNPC::getNpcRectangle()
{
    Rectangle(getMapDC(),m_garNorRc.left, m_garNorRc.top, m_garNorRc.right, m_garNorRc.bottom);
}
