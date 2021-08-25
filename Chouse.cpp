#include "framework.h"
#include "Chouse.h"
#include "camera.h"
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
    IMAGE->findImage("마리오집")->render(getMapDC());
}
