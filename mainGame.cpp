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
	   
	m_image = new Cimage;
	m_image->init();

	//SCENE->addScene("����", new CsceneDungeon);
	//SCENE->changeScene("����ȭ��");
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	SAFE_DELETE(m_image);
	EFFECT->release();
	SCENE->release();
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

	SCENE->render();
	TIME->render(getMemDC());


	/////////////////////////////////////////////////////////
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
