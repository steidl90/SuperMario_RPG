#include"framework.h"
#include "loading.h"

loadItem::loadItem()
{
}

loadItem::~loadItem()
{
}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND::LOAD_KIND_IMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height, BOOL isTranns, COLORREF transColor)
{

	_kind = LOAD_KIND::LOAD_KIND_IMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTranns;
	_imageResource.transColor = transColor;


	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTranns, COLORREF transColor)
{
	_kind = LOAD_KIND::LOAD_KIND_IMAGE_2;

	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTranns;
	_imageResource.transColor = transColor;
	_imageResource.x = x;
	_imageResource.y = y;
	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTranns, COLORREF transColor)
{
	_kind = LOAD_KIND::LOAD_KIND_FRAMEIMAGE_0;

	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTranns;
	_imageResource.transColor = transColor;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	return S_OK;
}

HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTranns, COLORREF transColor)
{
	_kind = LOAD_KIND::LOAD_KIND_FRAMEIMAGE_1;

	memset(&_imageResource, 0, sizeof(tagImageResource));
	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTranns;
	_imageResource.transColor = transColor;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.x = x;
	_imageResource.y = y;
	return S_OK;
}

loading::loading()
{
}

loading::~loading()
{
}

HRESULT loading::init()
{
	// 처음 시작했을때 화면
	_backgraound = IMAGE->addImage("사나", "images/사나.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	// 로딩바 이미지

	_loadingBar = new progressBar;
	_loadingBar->init("images/progressBarFront.bmp", "images/progressBarBack.bmp", 100, WINSIZEY / 2 + 300, 600, 10);
	_loadingBar->setGauge(0,0);
	_currentGauge = 0;

	return S_OK;
}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update()
{
	_loadingBar->update();
}

void loading::render()
{
	_backgraound->render(getMemDC());
	_loadingBar->render();
}

void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL isTranns, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName,fileName, width, height, isTranns, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTranns, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName,x,y, width, height, isTranns, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTranns, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height,frameX,frameY, isTranns, transColor);
	_vLoadItem.push_back(item);
}

void loading::loadForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTranns, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName,x,y, width, height, frameX, frameY, isTranns, transColor);
	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	if(_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}
	loadItem* item = _vLoadItem[_currentGauge];
	tagImageResource img = item->getImageResource();

	
	switch (item->getLoadKind())
	{
	case LOAD_KIND::LOAD_KIND_IMAGE_0:
		IMAGE->addImage(img.keyName, img.width, img.height);
		break;
	case LOAD_KIND::LOAD_KIND_IMAGE_1:
		IMAGE->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
		break;
	case LOAD_KIND::LOAD_KIND_IMAGE_2:
		IMAGE->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
		break;
	case LOAD_KIND::LOAD_KIND_FRAMEIMAGE_0:
		IMAGE->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		break;
	case LOAD_KIND::LOAD_KIND_FRAMEIMAGE_1:
		IMAGE->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
		break;
	case LOAD_KIND::LOAD_KIND_SOUND:
		break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	_currentGauge++;

	return 0;
}
