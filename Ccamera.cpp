#include "framework.h"
#include "Ccamera.h"

Ccamera::Ccamera():camera_width(WINSIZEX), camera_height(WINSIZEY)
{
}

Ccamera::~Ccamera()
{
}

HRESULT Ccamera::init()
{
	camera_width = WINSIZEX;
	camera_height = WINSIZEY;
	return S_OK;
}

void Ccamera::release()
{
}

void Ccamera::update()
{
	camera_x1 = target_x - camera_width / 2;
	camera_y1 = target_y - camera_height / 2;
	camera_x2 = camera_x1 + camera_width;
	camera_y2 = camera_y1 + camera_height;

	if (camera_x1 < 0)
	{
		camera_x1 = 0;
		camera_x2 = camera_width;
	}
	if (camera_y1 < 0)
	{
		camera_y1 = 0;
		camera_y2 = camera_height;
	}
	if (camera_x2 > MAPSIZEX)
	{
		camera_x2 = MAPSIZEX;
		camera_x1 = camera_x2 - camera_width;

	}
	if (camera_y2 > MAPSIZEY)
	{
		camera_y2 = MAPSIZEY;
		camera_y1 = camera_y2 - camera_height;
	}
}

void Ccamera::render()
{
	/*TCHAR str[128];
	sprintf(str, "%d : %d", m_ptMouse.x, m_ptMouse.y);
	TextOut(getMemDC(), 100, 100, str, lstrlen(str));

	POINT map;
	map.x = m_ptMouse.x + camera_x1;
	map.y = m_ptMouse.y + camera_y1;
	sprintf(str, "%d : %d", map.x, map.y);
	TextOut(getMemDC(), 200, 100, str, lstrlen(str));*/
}