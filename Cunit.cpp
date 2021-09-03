#include "framework.h"
#include "Cunit.h"

Cunit::Cunit()
    :m_x(0), m_y(0), m_rc(RectMake(0, 0, 0, 0)), m_stats(), isFight(NULL)
{
}

Cunit::Cunit(float x, float y, RECT rc, stats stats)
    :m_x(x), m_y(y), m_rc(rc), m_stats(stats), isFight(NULL)
{
}