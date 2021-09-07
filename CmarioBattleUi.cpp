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
	ANIMATION->start("��ġ����");
	ANIMATION->start("���Ļ���");
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
	ZORDER->zorderAniRender(IMAGE->findImage("������������"), ZUNIT, 1, 100, 200, ANIMATION->findAnimation("����������"));
	ZORDER->zorderRender(IMAGE->findImage("ü��UI"), ZUNIT, 0, 125, 215);

	ZORDER->zorderAniRender(IMAGE->findImage("��ġ������"), ZUNIT, 1, 150, 150, ANIMATION->findAnimation("��ġ����"));
	ZORDER->zorderRender(IMAGE->findImage("ü��UI"), ZUNIT, 0, 175, 165);

	ZORDER->zorderAniRender(IMAGE->findImage("���ľ�����"), ZUNIT, 1, 200, 100, ANIMATION->findAnimation("���Ļ���"));
	ZORDER->zorderRender(IMAGE->findImage("ü��UI"), ZUNIT, 0, 225, 115);
}
