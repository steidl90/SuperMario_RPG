#pragma once
#include "gameNode.h"
class CprogressBar : public gameNode
{
private:
	RECT m_rcProgress;
	int m_x, m_y;
	int m_width;

	image* m_progressBarFront;
	image* m_progressBarBack;

public:

	CprogressBar();
	~CprogressBar();

	HRESULT init(char* frontImage, char* backImage, float x, float y, int width, int height);
	void release();
	void update();
	void render();

	void mapUpdate(float x, float y);
	void mapRender();
	void mapBossRender();


	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { m_x = x; }
	void setY(int y) { m_y = y; }

	RECT getRect()const { return m_rcProgress; }
};

