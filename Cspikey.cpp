#include "framework.h"
#include "Cspikey.h"

HRESULT Cspikey::init()
{
	m_ani = ANIMATION->findAnimation("가시돌이좌하");
	ANIMATION->start("가시돌이좌하");
	return S_OK;
}

void Cspikey::release()
{
}

void Cspikey::updata()
{
}

void Cspikey::render()
{
	ZORDER->zorderAniRender(IMAGE->findImage("가시돌이이동"), ZUNIT, 0, m_x, m_y, m_ani);
}

void Cspikey::attack()
{
}

void Cspikey::run()
{
}
