#include "framework.h"
#include "Cfacade.h"

Cfacade::Cfacade() :m_image(new Cimage), m_ani(new Canimation)
{
}

Cfacade::~Cfacade()
{
}

HRESULT Cfacade::init()
{
	m_image->init();
	m_ani->init();

	return S_OK;
}

void Cfacade::release()
{
	SAFE_DELETE(m_image);
	SAFE_DELETE(m_ani);
}