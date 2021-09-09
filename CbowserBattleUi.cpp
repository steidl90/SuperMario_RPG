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
	ANIMATION->start("���Ļ���");
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
	ZORDER->zorderAniRender(IMAGE->findImage("���ľ�����"), ZUNIT, 1, 200, 100, ANIMATION->findAnimation("���Ļ���"));
	ZORDER->zorderRender(IMAGE->findImage("ü��UI"), ZUNIT, 0, 225, 115);

	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 265, 123, hp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 285, 123, hp % 10, 0);

	ZORDER->zorderRender(IMAGE->findImage("������"), ZUNIT, 0, 305, 125);

	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 320, 123, maxhp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 340, 123, maxhp % 10, 0);
}
