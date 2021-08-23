#include "framework.h"
#include "frameObject.h"

HRESULT frameObject::init(int x, int y, KINDFRAMEOBJECT frameObject)
{
	ANIMATION->addDefAnimation("큰풀모션", "큰풀", 10, false, true);
	ANIMATION->start("큰풀모션");
	ANIMATION->addDefAnimation("작은풀1모션", "작은풀1", 10, false, true);
	ANIMATION->start("작은풀1모션");
	ANIMATION->addDefAnimation("작은풀2모션", "작은풀2", 10, false, true);
	ANIMATION->start("작은풀2모션");

	m_ani = ANIMATION->findAnimation("큰풀모션");
	m_ani2 = ANIMATION->findAnimation("작은풀1모션");
	m_ani3 = ANIMATION->findAnimation("작은풀2모션");

	m_x = x;
	m_y = y;
	m_objectRect = RectMake(m_x, m_y, IMAGE->findImage("큰풀")->getFrameWidth(), IMAGE->findImage("큰풀")->getFrameHeight());
	m_objectRect2 = RectMake(m_x, m_y, IMAGE->findImage("작은풀1")->getFrameWidth(), IMAGE->findImage("작은풀1")->getFrameHeight());
	m_objectRect3 = RectMake(m_x, m_y, IMAGE->findImage("작은풀2")->getFrameWidth(), IMAGE->findImage("작은풀2")->getFrameHeight());
	
	m_frameObjectKind = frameObject;
	return S_OK;

}

void frameObject::release()
{
	//ANIMATION->release();
}

void frameObject::update()
{

}

void frameObject::render()
{

	switch (m_frameObjectKind)
	{
	case KINDFRAMEOBJECT::GRASS_BIG:
		//Rectangle(getMapDC(), m_objectRect.left, m_objectRect.top, m_objectRect.right, m_objectRect.bottom);
		IMAGE->findImage("큰풀")->aniRender(getMapDC(), m_x, m_y, m_ani);
		break;
	case KINDFRAMEOBJECT::GRASS_SAMLL1:
		//Rectangle(getMapDC(), m_objectRect2.left, m_objectRect2.top, m_objectRect2.right, m_objectRect2.bottom);
		IMAGE->findImage("작은풀1")->aniRender(getMapDC(), m_x, m_y, m_ani2);
		break;
	case KINDFRAMEOBJECT::GRASS_SMALL2:
		//Rectangle(getMapDC(), m_objectRect3.left, m_objectRect3.top, m_objectRect3.right, m_objectRect3.bottom);
		IMAGE->findImage("작은풀2")->aniRender(getMapDC(), m_x, m_y, m_ani3);
		break;
	default:
		break;
	}
}

RECT frameObject::getRect()
{
	switch (m_frameObjectKind)
	{
	case KINDFRAMEOBJECT::GRASS_BIG:
		return m_objectRect;
		break;
	case KINDFRAMEOBJECT::GRASS_SAMLL1:
		return m_objectRect2;
		break;
	case KINDFRAMEOBJECT::GRASS_SMALL2:
		return m_objectRect3;
		break;
	default:
		return m_objectRect;
		break;
	}

}
