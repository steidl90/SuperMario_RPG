#include "framework.h"
#include "CpeachBattleUi.h"

CpeachBattleUi::CpeachBattleUi()
{
}

CpeachBattleUi::~CpeachBattleUi()
{
}

HRESULT CpeachBattleUi::init()
{
	ANIMATION->start("피치상태");

	return S_OK;
}

void CpeachBattleUi::release()
{
}

void CpeachBattleUi::update()
{
}

void CpeachBattleUi::render(int hp, int maxhp)
{
	ZORDER->zorderAniRender(IMAGE->findImage("피치아이콘"), ZUNIT, 1, 150, 150, ANIMATION->findAnimation("피치상태"));
	ZORDER->zorderRender(IMAGE->findImage("체력UI"), ZUNIT, 0, 175, 165);

	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 215, 173, hp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 235, 173, hp % 10, 0);

	ZORDER->zorderRender(IMAGE->findImage("슬래시"), ZUNIT, 0, 255, 175);

	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 270, 173, maxhp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("숫자"), ZUNIT, 0, 290, 173, maxhp % 10, 0);
}