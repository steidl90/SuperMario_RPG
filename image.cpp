#include"framework.h"
#include "image.h"
//알파블렌드를 사용하기 위해
#pragma comment(lib,"msimg32.lib")
image::image() : _imageInfo(NULL),
_fileName(NULL),
_isTrans(false),
_transColor(RGB(0, 0, 0))
{
}
image::~image() {}

HRESULT image::init(const int width, const int height)
{

	//이미지 정보가 있으면 해제해라
	if (_imageInfo != NULL)release();
	//DC가져오기(현재 윈도우에 대한 화면 DC를 임시로 가져옴)
	//CreateCompatibleDC: 비트맵을 출력하기 위해 메모리 DC를 만들어준다.
	// CreateCompatibleBitmap: 원본DC와 호환되는 비트맵 생성

	HDC hdc = GetDC(m_hWnd);

	//이미지 정보 생성
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//파일이름
	_fileName = NULL;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;//블렌딩 연산자


	//알파 블렌드 사용하기 위한 이미지 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//투명키 셋팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, const int width, const int height, bool isTrans, COLORREF transColor)
{

	if (fileName == NULL)return E_FAIL;
	if (_imageInfo != NULL)release();


	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;//블렌딩 연산자


	//알파 블렌드 사용하기 위한 이미지 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//파일이름
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);



	return S_OK;
}

HRESULT image::init(const char* fileName, const float x, const float y, const int width, const int height, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL) return E_FAIL;

	//이미지 정보가 널이 아니라면(이미지가 들어있다면) 해제해라
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//빈 DC영역을 생성
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//알파 블렌드 옵션

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;	//32비트인경우 AC_SRC_APLHA를 지정하고 그 외에는 0으로 지정함(그렇지 않으면 알파블렌딩 함수 사용 불가)
	_blendFunc.BlendOp = AC_SRC_OVER;	//블렌딩 연산자


										//알파블렌드 사용하기 위한 이미지 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;


	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);
}

HRESULT image::init(const char* fileName, const int width, const int height, const int frameX, const int frameY, bool isTrans, COLORREF transColor)
{
	if (fileName == NULL)return E_FAIL;
	if (_imageInfo != NULL)release();


	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//알파 블렌드 옵션
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;//블렌딩 연산자


	//알파 블렌드 사용하기 위한 이미지 초기화
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//파일이름
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);
	return S_OK;
}

HRESULT image::init(const char* fileName, const int x, const int y, const int width, const int height, const int frameX, const int frameY, bool isTrans, COLORREF transColor)
{

	if (fileName == NULL)return E_FAIL;
	if (_imageInfo != NULL)release();


	HDC hdc = GetDC(m_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(m_hInstance,
		fileName,
		IMAGE_BITMAP,
		width, height,
		LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);

	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일이름
	int len = _tcslen(fileName);
	_fileName = new char[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_isTrans = isTrans;
	_transColor = transColor;

	//리소스를 얻어오는데 실패하면
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(m_hWnd, hdc);
	return S_OK;
}

HRESULT image::initForRotate()
{
	HDC hdc = GetDC(m_hWnd);

	int size;
	(_imageInfo->width > _imageInfo->height ? size = _imageInfo->width : size = _imageInfo->height);
	_rotateImage = new IMAGE_INFO;
	_imageInfo->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_FILE);
	_imageInfo->resID = 0;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, size, size);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = size;
	_rotateImage->height = size;

	ReleaseDC(m_hWnd, hdc);
	return S_OK;
}

HRESULT image::initForStretch()
{
	HDC hdc = GetDC(m_hWnd);

	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = static_cast<BYTE>(IMAGE_LOAD_KIND::LOAD_EMPTY);
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 5, WINSIZEY * 5);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);

	ReleaseDC(m_hWnd, hdc);

	return S_OK;
}


void image::setTransColor(bool isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_isTrans = false;
		_transColor = RGB(0, 0, 0);

	}
}

void image::render(HDC hdc)
{
	if (_isTrans)
	{
		//비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,						//복삳될 장소의 DC
			0,							//복사될 좌표의 시작점X
			0,							//복사될 좌표의 시작점Y
			_imageInfo->width,			//복사될 이미지 가로크기
			_imageInfo->height,			//복사될 이미지 세로크기
			_imageInfo->hMemDC,			//복사될 대상DC
			0,							//복사시작 지점 X
			0,							//복사시작 지점 Y
			_imageInfo->width,			//복사영역 가로크기
			_imageInfo->height,			//복사영역 세로크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속복사
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, const int destX, const int destY)
{
	if (_isTrans)
	{
		//비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,						//복삳될 장소의 DC
			destX,							//복사될 좌표의 시작점X
			destY,							//복사될 좌표의 시작점Y
			_imageInfo->width,			//복사될 이미지 가로크기
			_imageInfo->height,			//복사될 이미지 세로크기
			_imageInfo->hMemDC,			//복사될 대상DC
			0,							//복사시작 지점 X
			0,							//복사시작 지점 Y
			_imageInfo->width,			//복사영역 가로크기
			_imageInfo->height,			//복사영역 세로크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속복사
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}

}

void image::render(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourheight)
{
	if (_isTrans)
	{
		//비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,						//복삳될 장소의 DC
			destX,							//복사될 좌표의 시작점X
			destY,							//복사될 좌표의 시작점Y
			sourWidth,					//복사될 이미지 가로크기
			sourheight,			//복사될 이미지 세로크기
			_imageInfo->hMemDC,			//복사될 대상DC
			sourX,							//복사시작 지점 X
			sourY,							//복사시작 지점 Y
			sourWidth,			//복사영역 가로크기
			sourheight,			//복사영역 세로크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속복사
		BitBlt(hdc, destX, destY, sourWidth, sourheight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::mapRender(HDC hdc, const int destX, const int destY)
{
	if (_isTrans)
	{
		//비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,						//복삳될 장소의 DC
			destX,							//복사될 좌표의 시작점X
			destY,							//복사될 좌표의 시작점Y
			_imageInfo->width,			//복사될 이미지 가로크기
			_imageInfo->height,			//복사될 이미지 세로크기
			_imageInfo->hMemDC,			//복사될 대상DC
			0,							//복사시작 지점 X
			0,							//복사시작 지점 Y
			_imageInfo->width,			//복사영역 가로크기
			_imageInfo->height,			//복사영역 세로크기
			_transColor);
	}
	//TODO::미니맵 사이즈 수정할곳 _imageInfo->width/10, _imageInfo->height/10,
	else {
		//이미지의 크기를 조절하여 화면에 출력해주는 함수
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, destX, destY, _imageInfo->width/10, _imageInfo->height/10,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::reverseRender(HDC hdc, const int destX, const int destY)
{
	if (_isTrans)
	{
		//비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,						//복삳될 장소의 DC
			destX,							//복사될 좌표의 시작점X
			destY,							//복사될 좌표의 시작점Y
			_imageInfo->width,			//복사될 이미지 가로크기
			_imageInfo->height,			//복사될 이미지 세로크기
			_imageInfo->hMemDC,			//복사될 대상DC
			0,							//복사시작 지점 X
			0,							//복사시작 지점 Y
			_imageInfo->width,			//복사영역 가로크기
			_imageInfo->height,			//복사영역 세로크기
			_transColor);

		StretchBlt(hdc, destX, destY, -_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);

	}
	//TODO::미니맵 사이즈 수정할곳 _imageInfo->width/10, _imageInfo->height/10,
	else {
		//이미지의 크기를 조절하여 화면에 출력해주는 함수
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, destX, destY, -_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, const int destX, const int destY)
{
	if (_isTrans)
	{
		//비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,													//복삳될 장소의 DC
			destX,													//복사될 좌표의 시작점X
			destY,													//복사될 좌표의 시작점Y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사시작 지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사시작 지점 Y
			_imageInfo->frameWidth,									//복사영역 가로크기
			_imageInfo->frameHeight,								//복사영역 세로크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속복사
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY)
{

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_isTrans)
	{
		//비트맵을 불러올때 특정 색상을 제외하고 복사해주는 함수
		GdiTransparentBlt(
			hdc,													//복삳될 장소의 DC
			destX,													//복사될 좌표의 시작점X
			destY,													//복사될 좌표의 시작점Y
			_imageInfo->frameWidth,									//복사될 이미지 가로크기
			_imageInfo->frameHeight,								//복사될 이미지 세로크기
			_imageInfo->hMemDC,										//복사될 대상DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사시작 지점 X
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사시작 지점 Y
			_imageInfo->frameWidth,									//복사영역 가로크기
			_imageInfo->frameHeight,								//복사영역 세로크기
			_transColor);
	}
	else {
		//BitBlt : DC영역끼리 고속복사
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::alphaframeRender(HDC hdc, const int destX, const int destY, const int currentFrameX, const int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendFunc);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//보정하기
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);


	//그려지는(복사되어오는 이미지 영역)
	RECT rcSour;


	int sourWidth;
	int sourHeight;

	//그려지는 DC영역
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;


	//세로 루프영역
	for (size_t y = 0; y < drawAreaH; y += sourHeight)
	{
		//영역의  높이 계산하자
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀을 값을 올려줌
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (size_t x = 0; x < drawAreaW; x += sourWidth)
		{
			//영역계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//화면밖으로 넘어 갔다면
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//그리자
			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//보정하기
	if (offsetX < 0)offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0)offsetY = _imageInfo->height + (offsetY % _imageInfo->height);


	//그려지는(복사되어오는 이미지 영역)
	RECT rcSour;


	int sourWidth;
	int sourHeight;

	//그려지는 DC영역
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (size_t y = 0; y < drawAreaH; y += sourHeight)
	{
		//영역의  높이 계산하자
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀을 값을 올려줌
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (size_t x = 0; x < drawAreaW; x += sourWidth)
		{
			//영역계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//화면밖으로 넘어 갔다면
			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;


			//그리자
			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);

		}
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
}

void image::alphaRender(HDC hdc, const int destX, const int destY, BYTE alpha)
{
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);

	}
}

void image::alphaRender(HDC hdc, const int destX, const int destY, const int sourX, const int sourY, const int sourWidth, const int sourHeight, BYTE alpha)
{
	//알파값 초기화
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight, _imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);

	}
}

void image::rotateRender(HDC hdc, float centerX, float centerY, float angle)
{
	if (!_rotateImage) this->initForRotate();
	POINT rPoint[3];
	int dist = sqrt((_imageInfo->width / 2) * (_imageInfo->width / 2) + (_imageInfo->height / 2) * (_imageInfo->height / 2));
	float baseAngle[3];
	baseAngle[0] = PI - atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[1] = atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));
	baseAngle[2] = PI + atanf(((float)_imageInfo->height / 2) / ((float)_imageInfo->width / 2));

	for (int i = 0; i < 3; i++)
	{
		rPoint[i].x = (_rotateImage->width / 2 + cosf(baseAngle[i] + angle) * dist);
		rPoint[i].y = (_rotateImage->height / 2 + -sinf(baseAngle[i] + angle) * dist);
	}

	if (_isTrans)
	{
		BitBlt(_rotateImage->hMemDC, 0, 0, _rotateImage->width, _rotateImage->height, hdc, 0, 0, BLACKNESS);
		HBRUSH hBrush = CreateSolidBrush(_transColor);
		HBRUSH oBrush = (HBRUSH)SelectObject(_rotateImage->hMemDC, hBrush);
		ExtFloodFill(_rotateImage->hMemDC, 1, 1, RGB(0, 0, 0), FLOODFILLSURFACE);
		DeleteObject(hBrush);

		PlgBlt(_rotateImage->hMemDC, rPoint, _imageInfo->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			NULL, 0, 0);
		GdiTransparentBlt(hdc,
			centerX - _rotateImage->width / 2,
			centerY - _rotateImage->height / 2,
			_rotateImage->width,
			_rotateImage->height,
			_rotateImage->hMemDC,
			0, 0,
			_rotateImage->width,
			_rotateImage->height,
			_transColor);
	}
	else
	{
		PlgBlt(hdc, rPoint, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, 0, 0);
	}
}

void image::aniRender(HDC hdc, const int destX, const int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

//알파프레임렌더 추가 했음..
void image::alphaFrameRender(HDC hdc, const int destX, const int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}

}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_isTrans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_transColor);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);

		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendFunc);
	}
}

void image::stretchRender(HDC hdc, int centerX, int centerY, int newWidth, int newHeight)
{
	if (!_stretchImage) this->initForStretch();
	_stretchImage->width = newWidth;
	_stretchImage->height = newHeight;

	if (_isTrans)
	{
		//원본이미지를 Scale값 만큼 확대/축소시켜서 그려준다
		SetStretchBltMode(_stretchImage->hMemDC, COLORONCOLOR);
		StretchBlt(_stretchImage->hMemDC, 0, 0, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
		GdiTransparentBlt(
			hdc,					//복사할 장소의 DC
			centerX - _stretchImage->width / 2,					//복사될 좌표 시작점 X
			centerY - _stretchImage->height / 2,					//복사될 좌표 시작점 Y
			_stretchImage->width,	//복사될 이미지 가로크기
			_stretchImage->height,	//복사될 이미지 세로크기
			_stretchImage->hMemDC,	//복사될 대상 DC
			0, 0,					//복사 시작지점
			_stretchImage->width,	//복사 영역 가로크기
			_stretchImage->height,	//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (마젠타)
	}
	else {
		//원본 이미지의 크기를 확대/축소 해서 렌더 시킨다
		SetStretchBltMode(hdc, COLORONCOLOR);
		StretchBlt(hdc, centerX - _stretchImage->width / 2, centerY - _stretchImage->height / 2, _stretchImage->width, _stretchImage->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}
