#include "framework.h"
#include "Cskytroopa.h"

HRESULT Cskytroopa::init()
{
	m_ani = ANIMATION->findAnimation("≥Ø∞≥∞≈∫œ¿Ã¡¬«œ");
	ANIMATION->start("≥Ø∞≥∞≈∫œ¿Ã¡¬«œ");
	return S_OK;
}

void Cskytroopa::release()
{
}

void Cskytroopa::updata()
{
}

void Cskytroopa::render()
{
	ZORDER->zorderAniRender(IMAGE->findImage("≥Ø∞≥∞≈∫œ¿Ã¿Ãµø"), ZUNIT, 0, m_x, m_y, m_ani);
}

void Cskytroopa::attack()
{
}

void Cskytroopa::run()
{
}
