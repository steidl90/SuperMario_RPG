#include "framework.h"
#include "CmarioBattleUi.h"

CmarioBattleUi::CmarioBattleUi()
{
}

CmarioBattleUi::~CmarioBattleUi()
{
}

HRESULT CmarioBattleUi::init()
{
	ANIMATION->start("����������");
	ANIMATION->start("���Ļ���");
    return S_OK;
}

void CmarioBattleUi::release()
{
}

void CmarioBattleUi::update()
{
}

void CmarioBattleUi::render(int hp, int maxhp)
{
	ZORDER->zorderAniRender(IMAGE->findImage("������������"), ZUNIT, 1, 100, 200, ANIMATION->findAnimation("����������"));
	ZORDER->zorderRender(IMAGE->findImage("ü��UI"), ZUNIT, 0, 125, 215);

	ZORDER->zorderAniRender(IMAGE->findImage("���ľ�����"), ZUNIT, 1, 200, 100, ANIMATION->findAnimation("���Ļ���"));
	ZORDER->zorderRender(IMAGE->findImage("ü��UI"), ZUNIT, 0, 225, 115);

	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 165, 223, hp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 185, 223, hp % 10, 0);

	ZORDER->zorderRender(IMAGE->findImage("������"), ZUNIT, 0, 205, 225);

	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 220, 223, maxhp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 240, 223, maxhp % 10, 0);
}
