#pragma once
#include "gameNode.h"
class CsceneEnding : public gameNode
{
private:

public:
	CsceneEnding();
	~CsceneEnding() = default;

	HRESULT init();
	void update();
	void render();

	void sceneChange();
};