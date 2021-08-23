#pragma once
#include"gameNode.h"
#include"progressBar.h"
enum class LOAD_KIND
{
	LOAD_KIND_IMAGE_0, // 빈 비트맵 이미지
	LOAD_KIND_IMAGE_1, // 일반 이미지
	LOAD_KIND_IMAGE_2, // 일반 이미지(좌표 있음)
	LOAD_KIND_FRAMEIMAGE_0, // 프레임
	LOAD_KIND_FRAMEIMAGE_1, // 프레임(좌표 있음)
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource
{
	string keyName;	// 키값
	const char* fileName;	//이름
	int x, y;	//좌표
	int width, height;	//가로세로크기
	int frameX, frameY; // 프레임
	bool trans;		// 날릴꺼냐
	COLORREF transColor;
};

class loadItem
{
private:

	LOAD_KIND _kind;
	tagImageResource _imageResource;
public:
	loadItem();
	~loadItem();

	// 
	HRESULT initForImage(string keyName, int width, int height);

	HRESULT initForImage(string keyName, const char* fileName, int width, int height, BOOL isTranns = FALSE, COLORREF transColor = RGB(255,0,255));
	HRESULT initForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTranns = FALSE, COLORREF transColor = RGB(255,0,255));
	
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTranns = FALSE, COLORREF transColor = RGB(255,0,255));
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTranns = FALSE, COLORREF transColor = RGB(255,0,255));

	LOAD_KIND getLoadKind()const { return (LOAD_KIND)_kind; }
	// 이미지 리소스 가져오기
	tagImageResource getImageResource()const { return _imageResource; }

};

class loading : public gameNode
{

private:

	typedef vector<loadItem*> arrLoadItem;

	arrLoadItem _vLoadItem;

	image* _backgraound;
	progressBar* _loadingBar;

	int _currentGauge;

public:

	loading();
	~loading();

	HRESULT init();
	void release();
	void update();
	void render();

	void loadImage(string keyName, int width, int height);
	
	void loadImage(string keyName, const char* fileName, int width, int height, BOOL isTranns = FALSE, COLORREF transColor = RGB(255, 0, 255));
	void loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTranns = FALSE, COLORREF transColor = RGB(255, 0, 255));
	
	void loadForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTranns = FALSE, COLORREF transColor = RGB(255, 0, 255));
	void loadForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTranns = FALSE, COLORREF transColor = RGB(255, 0, 255));

	// 로딩 완료됐냐?
	BOOL loadingDone();

	vector<loadItem*>getLoadItem()const { return _vLoadItem; }
};

