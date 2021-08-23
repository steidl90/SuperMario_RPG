#include "framework.h"
#include "CNPC.h"

HRESULT CNPC::init()
{
    m_isAni = true;
    //���븣
    m_garNorImage = IMAGE->findImage("NPC���븣");
    ANIMATION->addDefAnimation("���븣", "NPC���븣", 8, false, true);
    m_garNorAni = ANIMATION->findAnimation("���븣");
    m_garNorX = 1000;
    m_garNorY = 550;
    
    //��Ű��
    m_shopKeeperImage = IMAGE->findImage("NPC��Ű��");
    ANIMATION->addDefAnimation("��Ű��", "NPC��Ű��",10, false, true);
    m_shopKeeperAni = ANIMATION->findAnimation("��Ű��");
    m_shopKeeperX = 470;
    m_shopKeeperY = 580;

    //������
    m_blackMarketImage = IMAGE->findImage("NPC������");
    ANIMATION->addDefAnimation("������", "NPC������",10, false, true);
    m_blackMarketAni = ANIMATION->findAnimation("������");
    m_blackMarketX = 1300;
    m_blackMarketY = 710;

    //�������
    m_edwardImage = IMAGE->findImage("NPC�������");
    ANIMATION->addDefAnimation("�������", "NPC�������", 5, false, true);
    m_edwardAni = ANIMATION->findAnimation("�������");
    m_edwardX = 685;
    m_edwardY = 550;

    //����
    m_ericImage = IMAGE->findImage("NPC����");
    ANIMATION->addDefAnimation("����", "NPC����", 10, false, true);
    m_ericAni = ANIMATION->findAnimation("����");
    m_ericX = 328;
    m_ericY = 230;

    //�ҽ�����
    m_halsteinImage = IMAGE->findImage("NPC�ҽ�����");
    ANIMATION->addDefAnimation("�ҽ�����", "NPC�ҽ�����", 10, false, true);
    m_halsteinAni = ANIMATION->findAnimation("�ҽ�����");
    m_halsteinX = 1500;
    m_halsteinY = 530;
   
    //ī�ϸ���
    m_kaylaImage=IMAGE->findImage("NPCī�ϸ���");
    ANIMATION->addDefAnimation("ī�ϸ���", "NPCī�ϸ���", 10, false, true);
    m_kaylaAni = ANIMATION->findAnimation("ī�ϸ���");
    m_kaylaX = 435;
    m_kaylaY = 1130;

    //��ĳ����
    m_sarcasterImage = IMAGE->findImage("NPC��ĳ����");
    ANIMATION->addDefAnimation("��ĳ����", "NPC��ĳ����", 8, false, true);
    m_sarcasterAni = ANIMATION->findAnimation("��ĳ����");
    m_sarcasterX = 220;
    m_sarcasterY = 1500;

    //�佺����
    m_torsteinImage = IMAGE->findImage("NPC�佺����");
    ANIMATION->addDefAnimation("�佺����", "NPC�佺����", 10, false, true);
    m_torsteinAni = ANIMATION->findAnimation("�佺����");
    m_torsteinX = 1170;
    m_torsteinY = 1380;

    //��ġ
    m_witchImage = IMAGE->findImage("NPC��ġ");
    ANIMATION->addDefAnimation("��ġ", "NPC��ġ", 10, false, true);
    m_witchAni = ANIMATION->findAnimation("��ġ");
    m_witchX = 540;
    m_witchY = 240;

    //�������ڰ�
    IMAGE->findImage("�������ڰ�");
    ANIMATION->addDefAnimation("�������ڰ�", "�������ڰ�", 10, false, true);
    m_healingcrossAni = ANIMATION->findAnimation("�������ڰ�");

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
     
    //���븣
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_garNorX + 9, m_garNorY + 37, 100);
    m_garNorImage->aniRender(getMapDC(), m_garNorX, m_garNorY, m_garNorAni);
    //��Ű��
    IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), m_shopKeeperX - 3, m_shopKeeperY + 40, 100);
    m_shopKeeperImage->aniRender(getMapDC(), m_shopKeeperX, m_shopKeeperY, m_shopKeeperAni);
    //������
    m_blackMarketImage->aniRender(getMapDC(), m_blackMarketX, m_blackMarketY, m_blackMarketAni);
    //�������
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_edwardX + 3, m_edwardY + 40, 100);
    m_edwardImage->aniRender(getMapDC(), m_edwardX, m_edwardY, m_edwardAni);
    //����
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_ericX - 3, m_ericY + 37, 100);
    m_ericImage->aniRender(getMapDC(), m_ericX, m_ericY, m_ericAni);
    //�ҽ�����
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_halsteinX - 1, m_halsteinY + 55, 100);
    m_halsteinImage->aniRender(getMapDC(), m_halsteinX, m_halsteinY, m_halsteinAni);
    //ī�ϸ���
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_kaylaX - 3, m_kaylaY + 33, 100);
    m_kaylaImage->aniRender(getMapDC(), m_kaylaX, m_kaylaY, m_kaylaAni);
    IMAGE->findImage("�������ڰ�")->aniRender(getMapDC(), m_kaylaX-40, m_kaylaY, m_healingcrossAni);

    //��ĳ����
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_sarcasterX-1, m_sarcasterY + 37, 100);
    m_sarcasterImage->aniRender(getMapDC(), m_sarcasterX, m_sarcasterY, m_sarcasterAni);
    //�佺����
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_torsteinX + 8, m_torsteinY + 25, 100);
    m_torsteinImage->aniRender(getMapDC(), m_torsteinX, m_torsteinY, m_torsteinAni);
    //��ġ
    IMAGE->findImage("NPC�׸���")->alphaRender(getMapDC(), m_witchX + 1, m_witchY + 50, 100);
    m_witchImage->aniRender(getMapDC(), m_witchX, m_witchY, m_witchAni);
    

    if (m_isAni)
    {
        getNpcAni();
        m_isAni = false;
    }
}

void CNPC::getNpcAni()
{
    ANIMATION->start("���븣");
    ANIMATION->start("��Ű��");
    ANIMATION->start("������");
    ANIMATION->start("�������");
    ANIMATION->start("����");
    ANIMATION->start("�ҽ�����");
    ANIMATION->start("ī�ϸ���");
    ANIMATION->start("��ĳ����");
    ANIMATION->start("�佺����");
    ANIMATION->start("��ġ");
    ANIMATION->start("�������ڰ�");
}

void CNPC::getNpcRectangle()
{
    Rectangle(getMapDC(),m_garNorRc.left, m_garNorRc.top, m_garNorRc.right, m_garNorRc.bottom);
}
