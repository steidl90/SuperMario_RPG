#pragma once
#include "CaddImg.h"
class Cimage
{
private:
	vector<CaddImg*> m_vTotalImg;
	vector<string> m_vImageList;

	IMAGE_TYPE m_Type;
	string m_name;
	string m_imageUrl;
	COLORREF m_transColor;
	int m_width;
	int m_height;
	int m_frameX;
	int m_frameY;
	bool m_trans;

public:
	Cimage();
	~Cimage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void initImg();
};

