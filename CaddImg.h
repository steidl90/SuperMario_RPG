#pragma once


class CaddImg
{
private:
	string m_name;
	string m_imageUrl;
	IMAGE_TYPE m_Type;
	COLORREF m_transColor;
	int m_width;
	int m_height;
	int m_frameX;
	int m_frameY;
	bool m_trans;

public:
	CaddImg();
	CaddImg(IMAGE_TYPE type, string url, string name, int const width, int const height, 
		int const frameX, int const frameY, bool trans, COLORREF transColor);
	~CaddImg();
};