#pragma once

class CaddImg
{
private:
	string m_name;
	string m_imageUrl;
	IMAGE_TYPE m_type;
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

	IMAGE_TYPE getType()const { return m_type; }
	COLORREF getColor()const { return m_transColor; }
	string getUrl()const { return m_imageUrl; }
	string getName()const { return m_name; }
	int getWidth()const { return m_width; }
	int getHeight()const { return m_height; }
	int getFrameX()const { return m_frameX; }
	int getFrameY()const { return m_frameY; }
	bool getTrans()const { return m_trans; }

};