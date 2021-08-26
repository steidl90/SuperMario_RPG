#pragma once
#include "image.h"
static image* backBuffer = IMAGE->addImage("backbuffer", WINSIZEX, WINSIZEY);
static image* mapBuffer = IMAGE->addImage("mapBuffer", MAPSIZEX, MAPSIZEY);

class gameNode
{
	HDC _hdc;
	bool  _managerInit;
	RECT _rect;

public:
	gameNode();
	virtual~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	image* getBackBuffer()const { return backBuffer; }
	image* getMapBuffer() const { return mapBuffer; }

	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return backBuffer->getMemDC(); }
	HDC getMapDC()const { return mapBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	RECT getClientRect() { return _rect; }
};