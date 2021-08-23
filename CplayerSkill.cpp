#include "framework.h"
#include "CplayerSkill.h"

CplayerSkill::CplayerSkill()
{
}

CplayerSkill::~CplayerSkill()
{
}

HRESULT CplayerSkill::init()
{
    skillDirection = SKILL::SKILL_DOWN;

	playerAttackDown = IMAGE->findImage("플레이어아래쪽공격");
	playerAttackLeft = IMAGE->findImage("플레이어왼쪽공격");
	playerAttackRight = IMAGE->findImage("플레이어오른쪽공격");
	playerAttackUp = IMAGE->findImage("플레이어위쪽공격");

	ANIMATION->addDefAnimation("위쪽공격", "플레이어위쪽공격", 20, false, true);
	ANIMATION->addDefAnimation("아래쪽공격", "플레이어아래쪽공격", 20, false, true);
	ANIMATION->addDefAnimation("왼쪽공격", "플레이어왼쪽공격", 20, false, true);
	ANIMATION->addDefAnimation("오른쪽공격", "플레이어오른쪽공격", 20, false, true);

	playerAttackAni = ANIMATION->findAnimation("아래쪽공격");


    return S_OK;
}

void CplayerSkill::release()
{
}

void CplayerSkill::update(const char* aniName)
{
	for (m_viPlayerSkill = m_vPlayerSkill.begin(); m_viPlayerSkill != m_vPlayerSkill.end();)
	{
		m_viPlayerSkill->m_fireX += cosf(m_viPlayerSkill->m_angle) * m_viPlayerSkill->m_speed;
		m_viPlayerSkill->m_fireY -= sinf(m_viPlayerSkill->m_angle) * m_viPlayerSkill->m_speed;

		m_viPlayerSkill->m_skillRc = RectMakeCenter(m_viPlayerSkill->m_fireX, m_viPlayerSkill->m_fireY,
			m_viPlayerSkill->m_skillImage->getFrameWidth(),
			m_viPlayerSkill->m_skillImage->getFrameHeight());

		if (m_viPlayerSkill->m_range < UTIL::getDistance(m_viPlayerSkill->m_fireX, m_viPlayerSkill->m_fireY,m_viPlayerSkill->m_skillX, m_viPlayerSkill->m_skillY))
		{
			m_viPlayerSkill = m_vPlayerSkill.erase(m_viPlayerSkill);
		}
		else ++m_viPlayerSkill;
	}
	ANIMATION->findAnimation(aniName);
	ANIMATION->resume(aniName);
	
}

void CplayerSkill::render()
{
	for (m_viPlayerSkill = m_vPlayerSkill.begin(); m_viPlayerSkill != m_vPlayerSkill.end(); ++m_viPlayerSkill)
	{
		m_viPlayerSkill->m_skillImage->aniRender(getMapDC(), m_viPlayerSkill->m_skillRc.left, m_viPlayerSkill->m_skillRc.top, m_viPlayerSkill->m_skillAni);
	}
	//Rectangle(getMapDC(), m_viPlayerSkill->m_skillRc.left, m_viPlayerSkill->m_skillRc.top, m_viPlayerSkill->m_skillRc.right, m_viPlayerSkill->m_skillRc.bottom);
}

void CplayerSkill::skillInformation(float x, float y, float angle, float speed, float range, const char* fileName,const char* aniName)
{
	tagPlayerSkill skill;
	ZeroMemory(&skill, sizeof(tagPlayerSkill));
	skill.m_skillImage = new image;
	skill.m_skillImage = IMAGE->findImage(fileName);
	skill.m_skillAni = ANIMATION->findAnimation(aniName);
	skill.m_angle = angle;
	skill.m_speed = speed;
	skill.m_skillX = skill.m_fireX = x;
	skill.m_skillY = skill.m_fireY = y;
	skill.m_range = range;
	skill.m_skillRc = RectMakeCenter(skill.m_skillX, skill.m_skillY, skill.m_skillImage->getFrameWidth(), skill.m_skillImage->getFrameHeight());
	m_vPlayerSkill.push_back(skill);
}

void CplayerSkill::removeSkill(int arrNum)
{
	m_vPlayerSkill.erase(m_vPlayerSkill.begin() + arrNum);
}
