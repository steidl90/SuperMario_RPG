#pragma once
#include"gameNode.h"
#include"progressBar.h"
enum class LOAD_KIND
{
	LOAD_KIND_IMAGE_0, // �� ��Ʈ�� �̹���
	LOAD_KIND_IMAGE_1, // �Ϲ� �̹���
	LOAD_KIND_IMAGE_2, // �Ϲ� �̹���(��ǥ ����)
	LOAD_KIND_FRAMEIMAGE_0, // ������
	LOAD_KIND_FRAMEIMAGE_1, // ������(��ǥ ����)
	LOAD_KIND_SOUND,
	LOAD_KIND_END
};

struct tagImageResource
{
	string keyName;	// Ű��
	const char* fileName;	//�̸�
	int x, y;	//��ǥ
	int width, height;	//���μ���ũ��
	int frameX, frameY; // ������
	bool trans;		// ��������
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
	// �̹��� ���ҽ� ��������
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

	// �ε� �Ϸ�Ƴ�?
	BOOL loadingDone();

	vector<loadItem*>getLoadItem()const { return _vLoadItem; }
};

