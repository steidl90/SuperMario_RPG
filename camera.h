#pragma once
#include "gameNode.h"
class camera : public gameNode
{
	int camera_x1, camera_y1;
	int camera_x2, camera_y2;

	int camera_width;
	int camera_height;

	int target_x, target_y;

public:
	camera();
	~camera();

	HRESULT init();
	void release();
	void update();
	void render();

	POINT getCameraPoint() { return PointMake(camera_x1, camera_y1); }
	POINT getCameraPoint2() { return PointMake(camera_x2, camera_y2); }

	int getCameraWidth() { return camera_width; }
	int getCameraHeight() { return camera_height; }

	void setTargetPoint(POINT p) { target_x = p.x; target_y = p.y; }

};