#include "framework.h"
#include "CresourceLoadFacade.h"

CresourceLoadFacade::CresourceLoadFacade() :m_image(new Cimage), m_ani(new Canimation)
{
}

CresourceLoadFacade::~CresourceLoadFacade()
{
}

HRESULT CresourceLoadFacade::init()
{
	m_image->init();
	m_ani->init();

	return S_OK;
}

void CresourceLoadFacade::release()
{
	SAFE_DELETE(m_image);
	SAFE_DELETE(m_ani);
}