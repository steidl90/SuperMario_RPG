#include "framework.h"
#include "Cunit.h"

Cunit::Cunit()
{
}

Cunit::Cunit(float x, float y, RECT rc, stats stats)
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

void Cunit::initAI(Cunit* monster, MONSTER_TYPE type)
{
}

void Cunit::updateAI()
{
}

STATE_TYPE Cunit::getstate()
{
    return STATE_TYPE();
}
