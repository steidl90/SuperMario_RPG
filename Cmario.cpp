#include "framework.h"
#include "Cmario.h"

Cmario::Cmario()
{
}

Cmario::Cmario(float x, float y, RECT rc, stats stats) :
    Cunit(x, y, rc, stats)
{
}

Cmario::~Cmario()
{
}

HRESULT Cmario::init()
{
    return S_OK;
}

void Cmario::release()
{
}

void Cmario::update()
{
    if (InputManager->isStayKeyDown(VK_LEFT))
    {
    }
    else if (InputManager->isStayKeyDown(VK_RIGHT))
    {

    }
    else if (InputManager->isStayKeyDown(VK_UP))
    {

    }
    else if (InputManager->isStayKeyDown(VK_DOWN))
    {

    }

    RectMake(m_x, m_y, IMAGE->findImage("마리오이동")->getFrameWidth(), IMAGE->findImage("마리오이동")->getFrameHeight());
}

void Cmario::render()
{
}
