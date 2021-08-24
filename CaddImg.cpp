#include "framework.h"
#include "CaddImg.h"

CaddImg::CaddImg()
{
}

CaddImg::CaddImg(IMAGE_TYPE type, string url, string name, int const width, int const height,
	int const frameX, int const frameY, bool trans, COLORREF transColor)
	:m_Type(type), m_imageUrl(url), m_name(name), m_width(width), m_height(height),
	m_frameX(frameX), m_frameY(frameY), m_trans(trans), m_transColor(transColor)
{
}

CaddImg::~CaddImg()
{
}
