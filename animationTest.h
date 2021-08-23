#pragma once
#include"gameNode.h"
#include"camel.h"
class animationTest :public gameNode
{
private:
	camel* _camel;
public:
	animationTest();
	~animationTest();

	HRESULT init();
	void release();
	void update();
	void render();
};

