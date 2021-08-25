#pragma once
#include "Cobject.h"

class Ccamera;
class Ctown :public Cobject
{
private:
	Ccamera* m_camera;

public:
	Ctown();
	~Ctown();

	HRESULT init();
	void release();
	void update();
	void render();

	void setCameraMemory(Ccamera* camera) { m_camera = camera; }
};

