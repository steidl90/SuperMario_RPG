#include "framework.h"
#include "CbanditsWay.h"

CbanditsWay::CbanditsWay()
{
}

CbanditsWay::~CbanditsWay()
{
}

HRESULT CbanditsWay::init()
{
    return S_OK;
}

void CbanditsWay::release()
{
}

void CbanditsWay::update()
{
}

void CbanditsWay::render()
{
    ZORDER->zorderRender(IMAGE->findImage("필드맵1"), ZMAP, 0, 0, 0);
    //ZORDER->zorderRender(IMAGE->findImage("마을맵제트오더"), ZABOVEMAP, 0, 0, 0);
}
