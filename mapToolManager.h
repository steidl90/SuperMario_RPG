#pragma once
#include"mapToolMain.h"
#include"mapToolSub.h"
#include"CTown.h"

class camera; // ī�޶� Ŭ���� ��ǥ���� �̿��ϱ� ���� ���漱������ ��������
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
