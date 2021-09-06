#pragma once
#include "singleton.h"
class Czorder : public Singleton<Czorder>
{
private:
	vector<tagZorder> _vZorder;

public:
	Czorder() {}
	~Czorder() {}

	void release();

	//��������
	void zorderRender(image* img, float z, float bottom, int destX, int destY);
	void zorderRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void zorderFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX = 0, int frameY = 0);
	void zorderAlphaRender(image* img, float z, float bottom, int destX, int destY, BYTE alpha);
	void zorderAlphaRender(image* img, float z, float bottom, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void zorderAlphaFrameRender(image* img, float z, float bottom, int destX, int destY, int frameX, int frameY, BYTE alpha);
	void zorderAniRender(image* img, float z, float bottom, int destX, int destY, animation* ani);

	void zorderRectangle(RECT rc, float z);


	//����
	inline void zorderSort();	//Z���� X, Y ������ ����
	static bool zordorCompare(const tagZorder& z1, const tagZorder& z2);	//��

	//���
	void zorderTotalRender(HDC hdc);
};