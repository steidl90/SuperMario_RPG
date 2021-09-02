#include "framework.h"
#include "Cgoomba.h"

HRESULT Cgoomba::init()
{
	m_ani = ANIMATION->findAnimation("굼바좌하");
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
	ZORDER->zorderAniRender(IMAGE->findImage("굼바이동"), ZUNIT, 0, 500, 500, m_ani);
}

void Cgoomba::attack()
{
	TextOut(getMemDC(), 100, 100, TEXT("테스트2"), lstrlen("테스트2"));
}

void Cgoomba::run()
{
}
