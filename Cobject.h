#pragma once
#include "gameNode.h"

class Cobject :public gameNode
{
private:

	/*
	타운 클래스와 던전 클래스에서 공통으로 필요한 부분은 여기에 만들어라
	타운 클래스와 던전 클래스에서 공통으로 필요한 부분은 여기에 만들어라
	타운 클래스와 던전 클래스에서 공통으로 필요한 부분은 여기에 만들어라
	*/

	// 임시 플레이어 스텟

public:
	Cobject();
	~Cobject();

	HRESULT init();
	void release();
	void update();
	void render();

	//============== get ==============//

	
	//============== set ==============//


};

