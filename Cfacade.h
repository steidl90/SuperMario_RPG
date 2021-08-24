#pragma once
#include "Cimage.h"
#include "Canimation.h"
class Cfacade
{
private:
	Cimage* m_image;
	Canimation* m_ani;

public:
	Cfacade();
	~Cfacade();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};