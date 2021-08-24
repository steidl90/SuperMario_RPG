#include "framework.h"
#include "Cfacade.h"

Cfacade::Cfacade()
{
}

Cfacade::~Cfacade()
{
}

HRESULT Cfacade::init()
{
	m_image = new Cimage;
	m_image->init();

	m_ani = new Canimation;
	m_ani->init();



	return S_OK;
}

void Cfacade::release()
{
	SAFE_DELETE(m_image);
	SAFE_DELETE(m_ani);
}

void Cfacade::update()
{
}

void Cfacade::render()
{
}
