#include "framework.h"
#include "Cgoomba.h"

HRESULT Cgoomba::init()
{
	m_ani = ANIMATION->findAnimation("±¿πŸ¡¬«œ");
	ANIMATION->start("±¿πŸ¡¬«œ");
    return S_OK;
}

void Cgoomba::release()
{
}

void Cgoomba::updata()
{
}

void Cgoomba::render()
{
	ZORDER->zorderAniRender(IMAGE->findImage("±¿πŸ¿Ãµø"), ZUNIT, 0, m_x, m_y, m_ani);
}

void Cgoomba::attack()
{

}

void Cgoomba::run()
{
}
