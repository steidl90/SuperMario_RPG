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

	m_player = new Cmario;
	m_player->init();

	//SCENE->addScene("던전", new CsceneDungeon);
	//SCENE->changeScene("시작화면");
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();
	EFFECT->release();
	SCENE->release();
	ANIMATION->release();
	SAFE_DELETE(m_facade);
	SAFE_DELETE(m_player);
}

void mainGame::update()
{
	gameNode::update();
	SCENE->update();
	m_player->update();
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

	m_player->render();
	SCENE->render();
	TIME->render(getMemDC());

	/////////////////////////////////////////////////////////
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
