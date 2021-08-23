#pragma once
#include"gameNode.h"

class frameObject : public gameNode
{
	RECT m_objectRect;
	RECT m_objectRect2;
	RECT m_objectRect3;

	KINDFRAMEOBJECT m_frameObjectKind;
	
	animation* m_ani;
	animation* m_ani2;
	animation* m_ani3;

	int m_x;
	int m_y;

public:
	HRESULT init(int x, int y, KINDFRAMEOBJECT frameObject);
	void release();
	void update();
	void render();

	RECT getRect();
};

