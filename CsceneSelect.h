#pragma once
#include "gameNode.h"
class CsceneSelect : public gameNode
{
private:
	animation* m_ani[15];
	RECT m_playerRc[15];

	int fps;

	bool isSelect;

public:
	CsceneSelect();
	~CsceneSelect();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageRender();
	void animation();
	void sceneChange();
	void shadowEffect();
	void selectEffect();
};