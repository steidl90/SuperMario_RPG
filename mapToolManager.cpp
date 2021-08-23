#include"framework.h"
#include "mapToolManager.h"
#include"camera.h"

HRESULT mapToolManager::init()
{
	// �ӽ� �߰� �̹���, ���߿� �Ѱ����� ���Ƽ� �Ҽ���
	

	m_mainMapTool = new mapToolMain;
	m_mainMapTool->init();

	m_subMapTool = new mapToolSub;
	m_subMapTool->init();
	
	m_subMapTool->setMapToolMainMemory(m_mainMapTool);
	m_mainMapTool->setCameraMemory(m_camera);

	return S_OK;
}

void mapToolManager::release()
{
	SAFE_DELETE(m_mainMapTool);
	SAFE_DELETE(m_subMapTool);
}

void mapToolManager::update()
{

	m_subMapTool->update();

	// ���밪 ��������ֱ�
	m_mainMapTool->setSubTile(m_subMapTool->getSubTile());
	m_mainMapTool->setMainMapCurrentTile(m_subMapTool->getCurrentTile());
	m_mainMapTool->setMainMapDragTile(m_subMapTool->getTagDragTile());
	m_mainMapTool->setMainMapSelect(m_subMapTool->getCtrlSelect());
	m_mainMapTool->setFrameKind(m_subMapTool->getFrameKind());

	m_mainMapTool->update();
}

void mapToolManager::render()
{

	m_mainMapTool->render();
	m_subMapTool->render();
	//m_mainMapTool->setSubTile(m_subMapTool->getSubTile());
}