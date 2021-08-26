#include"framework.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);

	m_facade = new Cfacade;
	m_facade->init();

	SCENE->addScene("����", new CsceneTown);
	SCENE->addScene("����������", new CsceneMarioHouse);
	SCENE->changeScene("����");
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	EFFECT->release();
	SCENE->release();
	ANIMATION->release();
	SAFE_DELETE(m_facade);
}

void mainGame::update()
{
	gameNode::update();
	SCENE->update();
	EFFECT->update();
	ANIMATION->update();
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	/////////////////////////////////////////////////////////

	// MapBuffer���� getMapDC�� �׷��� �� ��ü ũ���� �̹����� ����ִ�, MapBuffer�� render �Լ��� ����
	// ī�޶��� ���� x,y ��ǥ���� ���� ���� ���̸�ŭ ũ���� �̹����� �߶� (sour �μ��� �׷����)
	// �츮�� �� ȭ���� backBuffer�� getMemDC���ٰ� �׷��ش�

	//IMAGE->findImage("������")->render(getMemDC());
	SCENE->render();
	TIME->render(getMemDC());

	/////////////////////////////////////////////////////////
	RECT rc = checkGameSize();
	this->getBackBuffer()->stretchRender(getHDC(), RectCenterX(rc), RectCenterY(rc), RectWidth(rc), RectHeight(rc));
	//this->getBackBuffer()->render(getHDC(), 0, 0);
}

RECT mainGame::checkGameSize()
{
	RECT rc = this->getClientRect();
	float wid = rc.right;
	float hei = rc.bottom;
	float widOverHei = (float)WINSIZEX / WINSIZEY;
	float heiOverWid = (float)WINSIZEY / WINSIZEX;

	float w, h;
	//���� ���ο� ���� ���ΰ� ���� â�� ���κ��� ũ�ٸ�, ���� ���ο� �����.
	(wid * heiOverWid > hei) ? w = hei * widOverHei, h = hei
		: w = wid, h = w * heiOverWid;

	int left, top, right, bottom;
	if (w < wid) {
		left = wid / 2 - w / 2;
		right = left + w;
		top = 0;
		bottom = h;
	}
	else {
		left = 0;
		right = w;
		top = hei / 2 - h / 2;
		bottom = top + h;
	}
	//MoveWindow(gethwnd(), left, top, right, bottom, TRUE);    // listbox�� size�� change
	return { left, top, right, bottom };
}
