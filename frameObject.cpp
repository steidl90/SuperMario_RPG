#include "framework.h"
#include "frameObject.h"

HRESULT frameObject::init(int x, int y, KINDFRAMEOBJECT frameObject)
{
	ANIMATION->addDefAnimation("ūǮ���", "ūǮ", 10, false, true);
	ANIMATION->start("ūǮ���");
	ANIMATION->addDefAnimation("����Ǯ1���", "����Ǯ1", 10, false, true);
	ANIMATION->start("����Ǯ1���");
	ANIMATION->addDefAnimation("����Ǯ2���", "����Ǯ2", 10, false, true);
	ANIMATION->start("����Ǯ2���");

	m_ani = ANIMATION->findAnimation("ūǮ���");
	m_ani2 = ANIMATION->findAnimation("����Ǯ1���");
	m_ani3 = ANIMATION->findAnimation("����Ǯ2���");

	m_x = x;
	m_y = y;
	m_objectRect = RectMake(m_x, m_y, IMAGE->findImage("ūǮ")->getFrameWidth(), IMAGE->findImage("ūǮ")->getFrameHeight());
	m_objectRect2 = RectMake(m_x, m_y, IMAGE->findImage("����Ǯ1")->getFrameWidth(), IMAGE->findImage("����Ǯ1")->getFrameHeight());
	m_objectRect3 = RectMake(m_x, m_y, IMAGE->findImage("����Ǯ2")->getFrameWidth(), IMAGE->findImage("����Ǯ2")->getFrameHeight());
	
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
		IMAGE->findImage("ūǮ")->aniRender(getMapDC(), m_x, m_y, m_ani);
		break;
	case KINDFRAMEOBJECT::GRASS_SAMLL1:
		//Rectangle(getMapDC(), m_objectRect2.left, m_objectRect2.top, m_objectRect2.right, m_objectRect2.bottom);
		IMAGE->findImage("����Ǯ1")->aniRender(getMapDC(), m_x, m_y, m_ani2);
		break;
	case KINDFRAMEOBJECT::GRASS_SMALL2:
		//Rectangle(getMapDC(), m_objectRect3.left, m_objectRect3.top, m_objectRect3.right, m_objectRect3.bottom);
		IMAGE->findImage("����Ǯ2")->aniRender(getMapDC(), m_x, m_y, m_ani3);
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
