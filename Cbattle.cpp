#include "framework.h"
#include "Cbattle.h"

Cbattle::Cbattle()
{
}

Cbattle::~Cbattle()
{
}

HRESULT Cbattle::init()
{
	return S_OK;
}

void Cbattle::release()
{
}

void Cbattle::update()
{
}

void Cbattle::render()
{
	ZORDER->zorderRender(IMAGE->findImage("πË∆≤∏ 1"), ZMAP, 0, 0, 0);
}
