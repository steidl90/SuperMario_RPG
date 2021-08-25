#pragma once
#include "Cobject.h"
class camera;
class Chouse :public Cobject
{
private:
	camera* m_camera;

public:
	Chouse();
	~Chouse();

	HRESULT init();
	void release();
	void update();
	void render();

	void setCameraMemory(camera* camera) { m_camera = camera; }
};
