#include "framework.h"
#include "CmonsterWorld.h"

CmonsterWorld::CmonsterWorld(float x, float y, RECT rc, stats stats, CHARACTER_TYPE type) :Cmonster(x, y, rc, stats), m_type(type), m_ani()
{
}

HRESULT CmonsterWorld::init()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::GOOMBA:
		m_ani = ANIMATION->findAnimation("±¿πŸ¡¬«œ");
		ANIMATION->start("±¿πŸ¡¬«œ");
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		m_ani = ANIMATION->findAnimation("≥Ø∞≥∞≈∫œ¿Ã¡¬«œ");
		ANIMATION->start("≥Ø∞≥∞≈∫œ¿Ã¡¬«œ");
		break;
	case CHARACTER_TYPE::SPIKEY:
		m_ani = ANIMATION->findAnimation("∞°Ω√µπ¿Ã¡¬«œ");
		ANIMATION->start("∞°Ω√µπ¿Ã¡¬«œ");
		break;
	}
	
	return S_OK;
}

void CmonsterWorld::release()
{
}

void CmonsterWorld::update()
{
}

void CmonsterWorld::render()
{
	switch (m_type)
	{
	case CHARACTER_TYPE::GOOMBA:
		ZORDER->zorderAniRender(IMAGE->findImage("±¿πŸ¿Ãµø"), ZUNIT, 0, m_x, m_y, m_ani);
		break;
	case CHARACTER_TYPE::SKYTROOPA:
		ZORDER->zorderAniRender(IMAGE->findImage("≥Ø∞≥∞≈∫œ¿Ã¿Ãµø"), ZUNIT, 0, m_x, m_y, m_ani);
		break;
	case CHARACTER_TYPE::SPIKEY:
		ZORDER->zorderAniRender(IMAGE->findImage("∞°Ω√µπ¿Ã¿Ãµø"), ZUNIT, 0, m_x, m_y, m_ani);
		break;
	}
}

void CmonsterWorld::attack()
{
}

void CmonsterWorld::move()
{
}
