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
	ANIMATION->start("��ġ����");

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
	ZORDER->zorderAniRender(IMAGE->findImage("��ġ������"), ZUNIT, 1, 150, 150, ANIMATION->findAnimation("��ġ����"));
	ZORDER->zorderRender(IMAGE->findImage("ü��UI"), ZUNIT, 0, 175, 165);

	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 215, 173, hp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 235, 173, hp % 10, 0);

	ZORDER->zorderRender(IMAGE->findImage("������"), ZUNIT, 0, 255, 175);

	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 270, 173, maxhp % 100 / 10, 0);
	ZORDER->zorderFrameRender(IMAGE->findImage("����"), ZUNIT, 0, 290, 173, maxhp % 10, 0);
}