#pragma once
#include "gameNode.h"
#include "Ccamera.h"
#include "Ctown.h"
#include "CplayerManager.h"
class CsceneTown : public gameNode
{
private:
	Ccamera* m_camera;
	Ctown* m_town;
	CplayerManager* m_playerM;

private:
	RECT m_door;

public:
	CsceneTown();
	~CsceneTown();

	HRESULT init();
	void release();
	void update();
	void render();

	void scenechange();

	void pixelCollision();
	
};