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
	ANIMATION->start("피치상태");
	ANIMATION->start("쿠파상태");
    return S_OK;
}

void CmarioBattleUi::release()
{
}

void CmarioBattleUi::update()
{
}

void CmarioBattleUi::render()
{
	ZORDER->zorderAniRender(IMAGE->findImage("마리오아이콘"), ZUNIT, 1, 100, 200, ANIMATION->findAnimation("마리오상태"));
	ZORDER->zorderRender(IMAGE->findImage("체력UI"), ZUNIT, 0, 125, 215);

	ZORDER->zorderAniRender(IMAGE->findImage("피치아이콘"), ZUNIT, 1, 150, 150, ANIMATION->findAnimation("피치상태"));
	ZORDER->zorderRender(IMAGE->findImage("체력UI"), ZUNIT, 0, 175, 165);

	ZORDER->zorderAniRender(IMAGE->findImage("쿠파아이콘"), ZUNIT, 1, 200, 100, ANIMATION->findAnimation("쿠파상태"));
	ZORDER->zorderRender(IMAGE->findImage("체력UI"), ZUNIT, 0, 225, 115);
}
