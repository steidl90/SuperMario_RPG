#pragma once
#include "Cimage.h"
#include "Canimation.h"
class CresourceLoadFacade
{
private:
	Cimage* m_image;
	Canimation* m_ani;

public:
	CresourceLoadFacade();
	~CresourceLoadFacade();

	virtual HRESULT init();
	virtual void release();
};