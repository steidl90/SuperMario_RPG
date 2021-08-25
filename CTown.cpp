#include "framework.h"
#include "Ctown.h"
#include "Ccamera.h"

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
    IMAGE->findImage("¸¶À»¸Ê")->render(getMapDC());
}
