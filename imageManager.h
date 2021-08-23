#pragma once
#include"singleton.h"
#include"image.h"
class imageManager : public Singleton<imageManager>
{
private:

	typedef map<string, image*> mapImageList;
	typedef map<string, image*>::iterator mapImageListIter;

	mapImageList _mImageList;


public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	//키값으로 빈 비트맵 초기화
	image* addImage(string strkey, const int width, const int height);
	image* addImage(string strkey, const char* fileName, const int width, const int height, bool trans, COLORREF transColor);
	image* addImage(string strkey, const char* fileName, const int x, const int y, const int width, const int height, bool trans, COLORREF transColor);


	//키값으로  프레임 이미지 초기화
	image* addFrameImage(string strkey, const char* fileName, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strkey, const char* fileName, const float x, const float y, const int width, const int height, const int frameX, const int frameY, bool trans, COLORREF transColor);


	//이미지를 찾아라
	image* findImage(string strkey);
	//이미지 키값으로 삭제
	bool deleteImage(string strkey);

	//이미지 전체삭제
	bool deleteAll();


	//렌더
	void render(string strkey, HDC hdc);
	void render(string strkey, HDC hdc, const int destX, const int destY);
	void render(string strkey, HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight);


	//프레임

	void frameRender(string strkey, HDC hdc, const int destX, const int destY);
	void frameRender(string strkey, HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY);

	void loopRender(string strkey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strkey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);











};
