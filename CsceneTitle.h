#pragma once
#include "gameNode.h"
class CsceneTitle :public gameNode
{
private:
	int m_alpha;

public:
	CsceneTitle();
	~CsceneTitle() = default;

	HRESULT init();
	void update();
	void render();

	void sceneChange();
};

