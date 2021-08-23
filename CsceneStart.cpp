#include "framework.h"
#include "CsceneStart.h"

CsceneStart::CsceneStart()
	:m_newStartRc(RectMakeCenter(WINSIZEX - 300, 350, IMAGE->findImage("�����ӹ�ư��Ȱ��ȭ")->getWidth(), IMAGE->findImage("�����ӹ�ư��Ȱ��ȭ")->getHeight())),
	m_loadRc(RectMakeCenter(WINSIZEX - 300, 450, IMAGE->findImage("�ҷ������ư��Ȱ��ȭ")->getWidth(), IMAGE->findImage("�ҷ������ư��Ȱ��ȭ")->getHeight())),
	m_exitRc(RectMakeCenter(WINSIZEX - 300, 550, IMAGE->findImage("�������ư��Ȱ��ȭ")->getWidth(), IMAGE->findImage("�������ư��Ȱ��ȭ")->getHeight()))
{
}

CsceneStart::~CsceneStart()
{
}

HRESULT CsceneStart::init()
{
	return S_OK;
}

void CsceneStart::release()
{
}

void CsceneStart::update()
{
	sceneChange();
}

void CsceneStart::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0);
	imageRender();
}

void CsceneStart::imageRender()
{
	IMAGE->render("����ȭ��", getMapDC());
	if (PtInRect(&m_newStartRc, m_ptMouse)) IMAGE->render("�����ӹ�ưȰ��ȭ", getMapDC(), m_newStartRc.left, m_newStartRc.top);
	else IMAGE->render("�����ӹ�ư��Ȱ��ȭ", getMapDC(), m_newStartRc.left, m_newStartRc.top);
	if (PtInRect(&m_loadRc, m_ptMouse)) IMAGE->render("�ҷ������ưȰ��ȭ", getMapDC(), m_loadRc.left, m_loadRc.top);
	else IMAGE->render("�ҷ������ư��Ȱ��ȭ", getMapDC(), m_loadRc.left, m_loadRc.top);
	if (PtInRect(&m_exitRc, m_ptMouse)) IMAGE->render("�������ưȰ��ȭ", getMapDC(), m_exitRc.left, m_exitRc.top);
	else IMAGE->render("�������ư��Ȱ��ȭ", getMapDC(), m_exitRc.left, m_exitRc.top);
}

void CsceneStart::sceneChange()
{
	if (PtInRect(&m_newStartRc, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) SCENE->changeScene("����ȭ��");
	else if (PtInRect(&m_loadRc, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) SCENE->changeScene("����ȭ��");
	else if (PtInRect(&m_exitRc, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) PostQuitMessage(0);
}
