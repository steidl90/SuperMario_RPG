#pragma once
#include "Cunit.h"
class CplayerAttack :public Cunit
{
private:

public:
	CplayerAttack();
	~CplayerAttack();

	HRESULT init();
	void release();
	void update();
	void render();
};