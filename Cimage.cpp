#include "framework.h"
#include "Cimage.h"
#include "CaddImg.h"

Cimage::Cimage()
{
}

Cimage::~Cimage()
{
}

HRESULT Cimage::init()
{
	m_vImageList = TXT->txtLoad("images/이미지리스트.csv");
	initImg();
	addImage();
	

	return S_OK;
}

void Cimage::addImage()
{
	for (int i = 0; i < m_vTotalImg.size(); ++i)
	{
		if (m_vTotalImg[i]->getType() == IMAGE_TYPE::IMG)
		{
			IMAGE->addImage(m_vTotalImg[i]->getName(), m_vTotalImg[i]->getUrl().c_str(), m_vTotalImg[i]->getWidth(), m_vTotalImg[i]->getHeight(), m_vTotalImg[i]->getTrans(), m_vTotalImg[i]->getColor());
		}
		else if(m_vTotalImg[i]->getType() == IMAGE_TYPE::FRAMEIMG)
		{
			IMAGE->addFrameImage(m_vTotalImg[i]->getName(), m_vTotalImg[i]->getUrl().c_str(), m_vTotalImg[i]->getWidth(), m_vTotalImg[i]->getHeight(), m_vTotalImg[i]->getFrameX(), m_vTotalImg[i]->getFrameY(), m_vTotalImg[i]->getTrans(), m_vTotalImg[i]->getColor());
		}
	}
}

void Cimage::initImg()
{
	for (int i = 0; i < m_vImageList.size(); i += 11)
	{
		if (stoi(m_vImageList[i]) == 0) m_Type = IMAGE_TYPE::IMG;
		else if (stoi(m_vImageList[i]) == 1) m_Type = IMAGE_TYPE::FRAMEIMG;

		m_imageUrl = m_vImageList[i + 1];
		m_name = m_vImageList[i + 2];
		m_width = stoi(m_vImageList[i + 3]);
		m_height = stoi(m_vImageList[i + 4]);
		m_frameX = stoi(m_vImageList[i + 5]);
		m_frameY = stoi(m_vImageList[i + 6]);
		m_trans = stoi(m_vImageList[i + 7]);
		m_transColor = RGB(stoi(m_vImageList[i + 8]), stoi(m_vImageList[i + 9]), stoi(m_vImageList[i + 10]));

		CaddImg* addimg = new CaddImg(m_Type, m_imageUrl, m_name, m_width, m_height, m_frameX, m_frameY, m_trans, m_transColor);
		m_vTotalImg.push_back(addimg);
	}
}
