#include "framework.h"
#include "Chouse.h"
Chouse::Chouse()
{
}

Chouse::~Chouse()
{
}

HRESULT Chouse::init()
{
    return S_OK;
}

void Chouse::release()
{
}

void Chouse::update()
{
}

void Chouse::render()
{
    ZORDER->zorderRender(IMAGE->findImage("��������"), ZMAP, 0, 0, 0);
    ZORDER->zorderRender(IMAGE->findImage("����������Ʈ����"), ZABOVEMAP, 0, 0, 0);
}
