#include "framework.h"
#include "CprogressBar.h"

CprogressBar::CprogressBar()
{
}

CprogressBar::~CprogressBar()
{
}

HRESULT CprogressBar::init(char* frontImage, char* backImage, float x, float y, int width, int height)
{
	m_x = x;
	m_y = y;

	m_rcProgress = RectMake(x, y, width, height);
	m_progressBarFront = new image;
	m_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	m_progressBarBack = new image;
	m_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));

	m_width = m_progressBarFront->getWidth();

	return S_OK;
}

void CprogressBar::release()
{
	SAFE_DELETE(m_progressBarFront);
	SAFE_DELETE(m_progressBarBack);
}

void CprogressBar::update()
{
	m_rcProgress = RectMakeCenter(m_x + m_progressBarBack->getWidth() / 2,
		m_y + m_progressBarBack->getHeight() / 2,
		m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
}

void CprogressBar::render()
{
	m_progressBarBack->render(getMemDC(), m_rcProgress.left, m_y, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
	m_progressBarFront->render(getMemDC(), m_rcProgress.left, m_y, 0, 0, m_width, m_progressBarBack->getHeight());
}

void CprogressBar::mapUpdate(float x, float y)
{
	m_rcProgress = RectMakeCenter(x + m_progressBarBack->getWidth() / 2,
		y + m_progressBarBack->getHeight() / 2,
		m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
}

void CprogressBar::mapRender()
{
	m_progressBarBack->render(getMapDC(), m_rcProgress.left, m_rcProgress.top, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
	m_progressBarFront->render(getMapDC(), m_rcProgress.left, m_rcProgress.top, 0, 0, m_width, m_progressBarBack->getHeight());
}

void CprogressBar::mapBossRender()
{
	m_progressBarBack->render(getMemDC(), m_rcProgress.left, m_rcProgress.top, 0, 0, m_progressBarBack->getWidth(), m_progressBarBack->getHeight());
	m_progressBarFront->render(getMemDC(), m_rcProgress.left, m_rcProgress.top, 0, 0, m_width, m_progressBarBack->getHeight());
}

void CprogressBar::setGauge(float currentGauge, float maxGauge)
{
	m_width = (currentGauge / maxGauge) * m_progressBarBack->getWidth();
}
