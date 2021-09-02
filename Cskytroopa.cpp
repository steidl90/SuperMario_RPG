#include "framework.h"
#include "Cskytroopa.h"

Cskytroopa::~Cskytroopa()
{
}

HRESULT Cskytroopa::init()
{
	return S_OK;
}

void Cskytroopa::release()
{
}

void Cskytroopa::updata()
{
}

void Cskytroopa::render()
{
	this->attack();
}

void Cskytroopa::attack()
{
	TextOut(getMemDC(), 200, 100, TEXT("테스트1"), lstrlen("테스트1"));
}
