#include "framework.h"
#include "Cunit.h"

Cunit::Cunit()
    :m_x(0), m_y(0), m_rc(RectMake(0, 0, 0, 0)), m_stats()
{
}

Cunit::Cunit(float x, float y, RECT rc, stats stats)
    :m_x(x), m_y(y), m_rc(rc), m_stats(stats)
{
}

Cunit::~Cunit()
{
}

HRESULT Cunit::init()
{
    return S_OK;
}

void Cunit::release()
{
}

void Cunit::update()
{
}

void Cunit::render()
{
}

