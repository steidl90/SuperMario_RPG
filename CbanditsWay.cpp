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
    ZORDER->zorderRender(IMAGE->findImage("�ʵ��1"), ZMAP, 0, 0, 0);
    //ZORDER->zorderRender(IMAGE->findImage("��������Ʈ����"), ZABOVEMAP, 0, 0, 0);
}
