#include "framework.h"
#include "CbowserBattleUi.h"

CbowserBattleUi::CbowserBattleUi()
{
}

CbowserBattleUi::~CbowserBattleUi()
{
}

HRESULT CbowserBattleUi::init()
{
	ANIMATION->start("쿠파상태");
	return S_OK;
}

void CbowserBattleUi::release()
{
}

void CbowserBattleUi::update()
{
}

void CbowserBattleUi::render(int hp, int maxhp)
{
	ZORDER->zorderAniRender(IMAGE->findImage("쿠파아이콘"), ZUNIT, 1, 200, 100, ANIMATION->findAnimation("쿠파상태"));
	ZORDER->zorderRender(IMAGE->findImage("체력UI"), ZUNIT, 0, 225, 115);

	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 265, 123, hp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 285, 123, hp % 10, 0);

	ZORDER->zorderRender(IMAGE->findImage("슬래시"), ZUNIT, 0, 305, 125);

	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 320, 123, maxhp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 340, 123, maxhp % 10, 0);
}
