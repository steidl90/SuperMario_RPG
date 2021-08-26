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

	SCENE->addScene("마을", new CsceneTown);
	SCENE->addScene("마리오의집", new CsceneMarioHouse);
	SCENE->changeScene("마을");
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

	// MapBuffer에는 getMapDC에 그려진 맵 전체 크기의 이미지가 들어있다, MapBuffer의 render 함수를 통해
	// 카메라의 시작 x,y 좌표부터 가로 세로 길이만큼 크기의 이미지를 잘라서 (sour 인수가 그런기능)
	// 우리가 볼 화면인 backBuffer쪽 getMemDC에다가 그려준다

	//IMAGE->findImage("마을맵")->render(getMemDC());
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
	//현재 가로에 맞춘 세로가 현재 창의 세로보다 크다면, 현재 세로에 맞춘다.
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
	//MoveWindow(gethwnd(), left, top, right, bottom, TRUE);    // listbox의 size를 change
	return { left, top, right, bottom };
}
