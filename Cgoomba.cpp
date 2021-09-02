#include "framework.h"
#include "Cgoomba.h"

Cgoomba::~Cgoomba()
{
}

HRESULT Cgoomba::init()
{
    return S_OK;
}

void Cgoomba::release()
{
}

void Cgoomba::updata()
{
}

void Cgoomba::render()
{
	this->attack();
}

void Cgoomba::attack()
{
	TextOut(getMemDC(), 100, 100, TEXT("테스트2"), lstrlen("테스트2"));
}
