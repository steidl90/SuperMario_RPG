#include "framework.h"
#include "CenemyAttack.h"

CenemyAttack::CenemyAttack(){}

CenemyAttack::~CenemyAttack(){}

HRESULT CenemyAttack::init(int skillMax, float range, bool melee, const char* aniName)
{
	ANIMATION->addDefAnimation("������ų�ִ�", "������", 10, false, true);
	ANIMATION->addDefAnimation("������Ȧ�ִ�", "������Ȧ", 10, false, true);
	ANIMATION->addDefAnimation("������Ż��ų�ִ�", "������Ż��ų3", 10, false, true);
	ANIMATION->addDefAnimation("��ġ��ų�ִ�", "��ġ��ų", 15, false, true);

	ANIMATION->addAnimation("��ũ������", "��ũ����", 0, 4,	 8, true, true);
	ANIMATION->addAnimation("��ũ������", "��ũ����", 5, 9,	 8, true, true);
	ANIMATION->addAnimation("��ũ���ݿ�", "��ũ����", 10, 14,	 8, true, true);
	ANIMATION->addAnimation("��ũ���ݻ�", "��ũ����", 15, 19,	 8, true, true);

	ANIMATION->addAnimation("������������", "����������", 0, 7, 8, true, true);
	ANIMATION->addAnimation("������������", "����������", 8, 15, 8, true, true);
	ANIMATION->addAnimation("���������ݿ�", "����������", 16, 23, 8, true, true);
	ANIMATION->addAnimation("���������ݻ�", "����������", 24, 31, 8, true, true);

	ANIMATION->addAnimation("�����Ӱ�����", "�����Ӱ���", 0, 10, 12,  false, true);
	ANIMATION->addAnimation("�����Ӱ�����", "�����Ӱ���", 12, 23, 12, false, true);
	ANIMATION->addAnimation("�����Ӱ��ݿ�", "�����Ӱ���", 24, 35, 12, false, true);
	ANIMATION->addAnimation("�����Ӱ��ݻ�", "�����Ӱ���", 36, 47, 12, false, true);


	m_ani = aniName;
	m_skillMax = skillMax;
	m_range = range;
	m_melee = melee;

	return S_OK;
}

HRESULT CenemyAttack::init2(int skillMax, float range, bool melee, const char* aniName)
{
	m_ani = aniName;
	m_skillMax = skillMax;
	m_range = range;
	m_melee = melee;

	return S_OK;
}

void CenemyAttack::release()
{
}

void CenemyAttack::update()
{
	if (m_melee)
	{
		for (m_viSkill = m_vSkill.begin(); m_viSkill != m_vSkill.end();)
		{
			m_viSkill->m_rc = RectMakeCenter(m_viSkill->m_x, m_viSkill->m_y,
				m_viSkill->m_skillImage->getFrameWidth(),
				m_viSkill->m_skillImage->getFrameHeight());
		m_count++;
			if (m_count >= m_range)
			{
				m_viSkill = m_vSkill.erase(m_viSkill);
				m_count = 0;
			}
			else ++m_viSkill;
		}
		ANIMATION->findAnimation(m_ani);
		//ANIMATION->resume(m_ani);
		ANIMATION->fullstart(m_ani);
	}
	if (!m_melee)
	{
		for (m_viSkill = m_vSkill.begin(); m_viSkill != m_vSkill.end();)
		{
			m_viSkill->m_x += cosf(m_viSkill->m_angle) * m_viSkill->m_speed;
			m_viSkill->m_y -= sinf(m_viSkill->m_angle) * m_viSkill->m_speed;

			m_viSkill->m_rc = RectMakeCenter(m_viSkill->m_x, m_viSkill->m_y,
				m_viSkill->m_skillImage->getFrameWidth(),
				m_viSkill->m_skillImage->getFrameHeight());
			if (m_range < UTIL::getDistance(m_viSkill->m_x, m_viSkill->m_y, m_viSkill->m_fireX, m_viSkill->m_fireY))
			{
				m_viSkill = m_vSkill.erase(m_viSkill);
			}
			else ++m_viSkill;
		}
		ANIMATION->findAnimation(m_ani);
		ANIMATION->resume(m_ani);
	}

}

void CenemyAttack::render()
{
	for (m_viSkill = m_vSkill.begin(); m_viSkill != m_vSkill.end(); ++m_viSkill)
	{
	//Rectangle(getMapDC(), m_viSkill->m_rc.left, m_viSkill->m_rc.top, m_viSkill->m_rc.right, m_viSkill->m_rc.bottom);
		m_viSkill->m_skillImage->aniRender(getMapDC(), m_viSkill->m_rc.left, m_viSkill->m_rc.top,m_viSkill->m_ani);
	}
}

void CenemyAttack::fire(float x, float y, float angle, float speed, const char* fileName, const char* aniName)
{
	tagSkill skill;
	ZeroMemory(&skill, sizeof(tagSkill));
	skill.m_skillImage = new image;
	skill.m_skillImage = IMAGE->findImage(fileName);
	skill.m_ani = ANIMATION->findAnimation(aniName);
	skill.m_angle = angle;
	skill.m_speed = speed;
	skill.m_x = skill.m_fireX = x;
	skill.m_y = skill.m_fireY = y;
	skill.m_rc = RectMakeCenter(skill.m_x, skill.m_y, skill.m_skillImage->getFrameWidth(), skill.m_skillImage->getFrameHeight());
	m_vSkill.push_back(skill);
}

void CenemyAttack::removeSkill(int arrNum)
{
	m_vSkill.erase(m_vSkill.begin() + arrNum);
}
