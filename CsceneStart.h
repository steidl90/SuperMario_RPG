#pragma once
#include "gameNode.h"
class CsceneStart : public gameNode
{
private:
	RECT m_newStartRc;
	RECT m_loadRc;
	RECT m_exitRc;

public:
	CsceneStart();
	~CsceneStart();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageRender();
	void sceneChange();
};

