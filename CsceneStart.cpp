#include "framework.h"
#include "CsceneStart.h"

CsceneStart::CsceneStart()
	:m_newStartRc(RectMakeCenter(WINSIZEX - 300, 350, IMAGE->findImage("새게임버튼비활성화")->getWidth(), IMAGE->findImage("새게임버튼비활성화")->getHeight())),
	m_loadRc(RectMakeCenter(WINSIZEX - 300, 450, IMAGE->findImage("불러오기버튼비활성화")->getWidth(), IMAGE->findImage("불러오기버튼비활성화")->getHeight())),
	m_exitRc(RectMakeCenter(WINSIZEX - 300, 550, IMAGE->findImage("나가기버튼비활성화")->getWidth(), IMAGE->findImage("나가기버튼비활성화")->getHeight()))
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
	IMAGE->render("시작화면", getMapDC());
	if (PtInRect(&m_newStartRc, m_ptMouse)) IMAGE->render("새게임버튼활성화", getMapDC(), m_newStartRc.left, m_newStartRc.top);
	else IMAGE->render("새게임버튼비활성화", getMapDC(), m_newStartRc.left, m_newStartRc.top);
	if (PtInRect(&m_loadRc, m_ptMouse)) IMAGE->render("불러오기버튼활성화", getMapDC(), m_loadRc.left, m_loadRc.top);
	else IMAGE->render("불러오기버튼비활성화", getMapDC(), m_loadRc.left, m_loadRc.top);
	if (PtInRect(&m_exitRc, m_ptMouse)) IMAGE->render("나가기버튼활성화", getMapDC(), m_exitRc.left, m_exitRc.top);
	else IMAGE->render("나가기버튼비활성화", getMapDC(), m_exitRc.left, m_exitRc.top);
}

void CsceneStart::sceneChange()
{
	if (PtInRect(&m_newStartRc, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) SCENE->changeScene("선택화면");
	else if (PtInRect(&m_loadRc, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) SCENE->changeScene("선택화면");
	else if (PtInRect(&m_exitRc, m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) PostQuitMessage(0);
}
