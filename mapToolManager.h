#pragma once
#include"mapToolMain.h"
#include"mapToolSub.h"
#include"CTown.h"

class camera; // 카메라 클래스 좌표정보 이용하기 위해 전방선언으로 가져오기
class mapToolManager : public gameNode
{
	mapToolMain* m_mainMapTool;
	mapToolSub* m_subMapTool;
	Ctown* m_town;
	camera* m_camera;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	mapToolMain* getMapToolMain() { return m_mainMapTool; }

	void setCameraMemory(camera* c) { m_camera = c; }
};
