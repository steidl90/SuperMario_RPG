#include "framework.h"
#include "Ctown.h"

Ctown::Ctown()
{
}

Ctown::~Ctown()
{
}

HRESULT Ctown::init()
{
    return S_OK;
}

void Ctown::release()
{
}

void Ctown::update()
{
}

void Ctown::render()
{
    ZORDER->zorderRender(IMAGE->findImage("������"), ZMAP, 0, 0, 0);
    ZORDER->zorderRender(IMAGE->findImage("��������Ʈ����"), ZABOVEMAP, 0, 0, 0);
}
