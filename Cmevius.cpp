#include "framework.h"
#include "Cmevius.h"
#include "CdropItem.h"

Cmevius::Cmevius()
{
    m_meviusImage = nullptr;
}

Cmevius::~Cmevius()
{
}

HRESULT Cmevius::init(POINT position, int hp, float p1Damage1)
{
    m_em = new CenemyManager;
    
    m_attack = new CenemyAttack;
    m_attack->init(100,800,false,"��ġ��ų�ִ�");
    m_hpBar = new CprogressBar;
    m_hpBar->init("images/hp.bmp", "images/hp_back.bmp", m_x, m_y, 596, 16);
    m_hpBar->setGauge(m_hp, m_maxHp);

	ANIMATION->addDefAnimation("�ִϰ���", "��������", 10, false, true);
    ANIMATION->addDefAnimation("�ִϺ���", "����", 5, false, true);
    ANIMATION->addDefAnimation("�ִ�ĳ����", "����ĳ����", 10, false, false);
    ANIMATION->addDefAnimation("�ִ�ĳ����2", "����ĳ����", 10, true, false);
    ANIMATION->addDefAnimation("�ִϰȱ�", "�����ȱ�", 3, false, false);
    ANIMATION->addDefAnimation("�ִϰ�", "������", 10, false, true);
    ANIMATION->addDefAnimation("����������2", "��������", 5, false, true);
    EFFECT->addEffect("����Ʈ��", "images/Lightning.bmp", 576, 402, 72, 402, 1, 0.15f, 100);
    EFFECT->addEffect("������", "images/Stomp.bmp", 819*3, 78*3, 91*3, 78*3, 1, 0.1f, 200);
    EFFECT->addEffect("�����ڷ���Ʈ", "images/Teleport.bmp", 1254*3, 316*3, 114*3,316*3, 1, 0.13f, 100);
    m_isAppear = true;
    m_isEffect = false;
    m_isLevitating = false;
	m_isWalking = false;
	m_isCasting = false;
	m_isIdle = false;
	m_isDie = false;

    m_x = position.x ;
    m_y = position.y;
    m_speed = 2;

    m_hp = m_maxHp = hp;

    m_skillDamagePattern1= p1Damage1;


    return S_OK;
}

void Cmevius::release()
{
    SAFE_DELETE(m_meviusImage);
}

void Cmevius::update()
{
    m_hpBar->setGauge(m_hp, m_maxHp);
    m_hpBar->mapUpdate(344,70);
    m_attack->update();
    //����� ����
   if (m_isAppear)
   {
       m_isLevitating = true;
       m_isAppear = false;
   }

    if (m_isLevitating)
    {
        m_effectCount++;
        if (m_effectCount % 4 == 0)
        {
            EFFECT->play("����Ʈ��", RND->getFromIntTo(100, WINSIZEX - 100), RND->getFromIntTo(100, WINSIZEY - 100));
        }
        m_meviusImage = IMAGE->findImage("��������");
        m_meviusAnimation = ANIMATION->findAnimation("�ִϰ���");
        ANIMATION->start("�ִϰ���");
        if (m_meviusRc.top <= 400) m_y += m_speed;
		else
		{
            m_ActionCount++;
			if (m_ActionCount == 50)
			{
				m_isEffect = false;
                m_isLevitating = false;
				m_isWalking = true;
                m_isIdle = true;
			EFFECT->play("������", m_meviusRc.left + (m_meviusRc.right - m_meviusRc.left) / 2, m_meviusRc.bottom);
			}
		}
	}
	if (m_isWalking)
	{
		m_meviusImage = IMAGE->findImage("�����ȱ�");
		m_meviusAnimation = ANIMATION->findAnimation("�ִϰȱ�");
		ANIMATION->start("�ִϰȱ�");
		m_isWalking = false;
	}

	if (!m_isAppear && !m_isWalking && m_meviusRc.top <= 450)
	{
		m_y += 0.2f;
	}

    if (m_meviusRc.top >= 450 && m_isIdle)
    {
        if (!m_isTeleport) {
            m_meviusImage = IMAGE->findImage("����");
            m_meviusAnimation = ANIMATION->findAnimation("�ִϺ���");
            ANIMATION->resume("�ִϺ���");
        }
        else
        {
            m_meviusImage = IMAGE->findImage("��������");
            m_meviusAnimation = ANIMATION->findAnimation("����������2");
            ANIMATION->resume("����������2");
        }
        meviusphase1();

    }
    //����� ��

    if ( InputManager->isOnceKeyDown('2'))
    {
        m_meviusImage = IMAGE->findImage("����ĳ����");
        m_meviusAnimation = ANIMATION->findAnimation("�ִ�ĳ����2");
        ANIMATION->resume("�ִ�ĳ����2");
        m_isIdle = true;
    }

    if (m_hp <= m_maxHp *0.8)
    {
        meviusphase2();
    }  
    if (m_hp <= m_maxHp * 0.5)
    {
        if (!m_isTeleport)
        {
            m_hp = m_maxHp;
            m_dropItem->makeFinalItem(m_x, m_y);
            EFFECT->play("�����ڷ���Ʈ", m_x+ (m_meviusImage->getFrameWidth()/2)-20, m_y-50);
        }
        m_isTeleport = true;
        meviusphase3();
        m_x = 900;
        m_y = 900;
        m_skillDamagePattern1 = 150;
    }


    if (InputManager->isStayKeyDown('6'))
    {
        m_hp -= 100;
    }

    if (m_meviusImage != nullptr) {
        m_meviusRc = RectMake(m_x, m_y, m_meviusImage->getFrameWidth(), m_meviusImage->getFrameHeight());
    }
}

void Cmevius::render()
{
    if (m_meviusImage != nullptr) 
    {
        EFFECT->render();
        //Rectangle(getMapDC(), m_meviusRc.left, m_meviusRc.top, m_meviusRc.right, m_meviusRc.bottom);
        m_attack->render();
        m_meviusImage->aniRender(getMapDC(), m_x, m_y, m_meviusAnimation);

        m_hpBar->mapBossRender();
        IMAGE->findImage("����ü�¹�")->render(getMemDC(),300,50 );
        TCHAR strhp[128];
        TCHAR strcoolTime[128];
        SetTextColor(getMemDC(), RGB(255, 255, 255));
        SetTextAlign(getMemDC(), TA_CENTER);
        sprintf_s(strhp, "%.0f/%.0f   ", m_hp, m_maxHp);
        TextOut(getMemDC(), 640, 70, strhp, strlen(strhp));
        SetTextAlign(getMemDC(), TA_LEFT);

    }
}

void Cmevius::meviusphase1()
{
    if (m_meviusImage != nullptr) {
        if (meviusCooltime(0, 50)) {
            for (size_t i = 0; i < 1; i++) {
                int count = 6;
                m_angle += 0.05;
                float tempAngle = 2 / (float)count;
                for (size_t j = 0; j < count; j++) {
                    m_attack->fire(m_meviusRc.right - (m_meviusRc.right - m_meviusRc.left) / 2,
                        m_meviusRc.bottom - (m_meviusRc.bottom - m_meviusRc.top) / 2,
                        (i * 0.2) + PI * tempAngle * j + m_angle, 4.0f, "������", "������ų�ִ�");
                }
            }
        }
    }
}

void Cmevius::meviusphase2()
{
    if (m_meviusImage != nullptr) {
        if (meviusCooltime(1,10)) {
            for (size_t i = 0; i < 1; i++) {
                int count = 4;
                m_angle += 0.10;
                float tempAngle = 2 / (float)count;
                for (size_t j = 0; j < count; j++) {
                    m_attack->fire(m_meviusRc.right - (m_meviusRc.right - m_meviusRc.left) / 2,
                        m_meviusRc.bottom - (m_meviusRc.bottom - m_meviusRc.top) / 2,
                        (i * 0.2) + PI * tempAngle * j + m_angle, 5.0f, "������", "������ų�ִ�");
                }
            }
        }
    }
}

void Cmevius::meviusphase3()
{
    if (m_meviusImage != nullptr) {
        if (meviusCooltime(2, 100)) {
            for (size_t i = 0; i < 1; i++) {
                int count = 3;
                m_angle += 0.1;
                float tempAngle = 2 / (float)count;
                for (size_t j = 0; j < count; j++) {
                    m_attack->fire(m_meviusRc.right - (m_meviusRc.right - m_meviusRc.left) / 2,
                        m_meviusRc.bottom - (m_meviusRc.bottom - m_meviusRc.top) / 2,
                        (i * 0.2) + PI * tempAngle * j - m_angle, 2.5f, "��ġ��ų", "��ġ��ų�ִ�");
                }
            }
        }
    }
}

void Cmevius::collision()
{
    if (m_attack)
    {
        for (size_t j = 0; j < m_attack->getVSkill().size(); j++)
        {
            RECT rc;
            if (IntersectRect(&rc, &m_attack->getVSkill()[j].m_rc, m_player->getplayerMoveRC()))
            {
                if (m_skillDamagePattern1 <= m_player->getDef())
                {
                    m_attack->removeSkill(j);
                }
                else
                {
                  m_attack->removeSkill(j);
                    m_player->setHp(m_player->getHp() - (m_skillDamagePattern1 - m_player->getDef()));
                }
            }
        }
    }
}

bool Cmevius::meviusCooltime(int ArrNum,int skillcount)
{
    m_coolTime[ArrNum]++;
    m_skillCount[ArrNum] = skillcount;

    if (m_coolTime[ArrNum] % skillcount == 0)
    {
        m_coolTime[ArrNum] = 0;
        return true;
    }
    return false;
}
