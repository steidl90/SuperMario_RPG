#include "framework.h"
#include "Cgoomba.h"

HRESULT Cgoomba::init()
{
	m_ani = ANIMATION->findAnimation("��������");
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
	ZORDER->zorderAniRender(IMAGE->findImage("�����̵�"), ZUNIT, 0, 500, 500, m_ani);
}

void Cgoomba::attack()
{
	TextOut(getMemDC(), 100, 100, TEXT("�׽�Ʈ2"), lstrlen("�׽�Ʈ2"));
}

void Cgoomba::run()
{
}
