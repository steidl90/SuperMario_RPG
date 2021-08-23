#pragma once
#include"gameNode.h"

class mainGame : public gameNode
{
private:
	Cimage* m_image;

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
