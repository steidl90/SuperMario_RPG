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
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
