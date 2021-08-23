#pragma once
#include"image.h"
#include"Cimage.h"
static image* backBuffer = IMAGE->addImage("backbuffer", WINSIZEX, WINSIZEY);
static image* mapBuffer = IMAGE->addImage("mapBuffer", MAPSIZE, MAPSIZE);
static image* tileBuffer = IMAGE->addImage("tileBuffer", MAPSIZE, MAPSIZE);

class gameNode
{

	//image* _backBuffer;	//백버퍼
	//void setBackBuffer();//백버퍼 셋팅

	HDC _hdc;
	bool  _managerInit;

public:
	gameNode();
	virtual~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);

	image* getBackBuffer()const { return backBuffer; }
	image* getMapBuffer() const { return mapBuffer; }
	image* getTileBuffer() const { return tileBuffer; }

	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return backBuffer->getMemDC(); }
	HDC getMapDC()const { return mapBuffer->getMemDC(); }
	HDC getTileDC()const { return tileBuffer->getMemDC(); }


	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};