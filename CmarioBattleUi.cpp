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
	ANIMATION->start("마리오상태");
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
	ZORDER->zorderAniRender(IMAGE->findImage("마리오아이콘"), ZUNIT, 1, 100, 200, ANIMATION->findAnimation("마리오상태"));
	ZORDER->zorderRender(IMAGE->findImage("체력UI"), ZUNIT, 0, 125, 215);

	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 165, 223, hp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 185, 223, hp % 10, 0);

	ZORDER->zorderRender(IMAGE->findImage("슬래시"), ZUNIT, 0, 205, 225);

	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 220, 223, maxhp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 240, 223, maxhp % 10, 0);
}
