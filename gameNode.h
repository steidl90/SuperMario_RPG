#pragma once
#include "image.h"
static image* backBuffer = IMAGE->addImage("backbuffer", WINSIZEX, WINSIZEY);

class gameNode
{

	HDC _hdc;
	bool  _managerInit;

public:
	gameNode();
	virtual~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render();

	image* getBackBuffer()const { return backBuffer; }
	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return backBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};