#pragma once
#include "Cobject.h"

class camera;
class Ctown :public Cobject
{
private:
	camera* m_camera;

public:
	Ctown();
	~Ctown();

	HRESULT init();
	void release();
	void update();
	void render();

	void setCameraMemory(camera* camera) { m_camera = camera; }
};

