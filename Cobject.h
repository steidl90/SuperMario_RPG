#pragma once
#include "gameNode.h"
class Cobject :public gameNode
{
private:


public:
	Cobject();
	~Cobject();

	HRESULT init();
	void release();
	void update();
	void render();
};


