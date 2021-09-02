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
}