#pragma once
#include "gameNode.h"
#include "camera.h"
#include "Ctown.h"
#include "CplayerManager.h"
class CsceneTown : public gameNode
{
private:
	camera* m_camera;
	Ctown* m_town;
	CplayerManager* m_player;
public:
	CsceneTown();
	~CsceneTown();

	HRESULT init();
	void release();
	void update();
	void render();

	
};