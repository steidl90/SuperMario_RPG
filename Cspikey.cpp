#include "framework.h"
#include "Cspikey.h"

HRESULT Cspikey::init()
{
	m_ani = ANIMATION->findAnimation("���õ�������");
	ANIMATION->start("���õ�������");
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
	ZORDER->zorderAniRender(IMAGE->findImage("���õ����̵�"), ZUNIT, 0, m_x, m_y, m_ani);
}

void Cspikey::attack()
{
}

void Cspikey::run()
{
}
