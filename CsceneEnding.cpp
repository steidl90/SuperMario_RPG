#include "framework.h"
#include "CsceneEnding.h"

CsceneEnding::CsceneEnding()
{
}

HRESULT CsceneEnding::init()
{
	m_alpha = 255;
	ANIMATION->start("���翣��");
	ANIMATION->start("����������");
	return S_OK;
}

void CsceneEnding::update()
{
	if (m_alpha > 0)
		m_alpha -= 5;
	sceneChange();
}

void CsceneEnding::render()
{
	ZORDER->zorderRender(IMAGE->findImage("�������"), ZMAP, 0, 0, 0);
	ZORDER->zorderAniRender(IMAGE->findImage("��������"), ZMAP, 1, 0, 0, ANIMATION->findAnimation("���翣��"));
	ZORDER->zorderAniRender(IMAGE->findImage("����������"), ZMAP, 1, WINSIZEX / 2 - 150, WINSIZEY - 300, ANIMATION->findAnimation("����������"));

	if (m_alpha > 0)
		ZORDER->zorderAlphaRender(IMAGE->findImage("����"), ZMAP, 2, 0, 0, m_alpha);
}

void CsceneEnding::sceneChange()
{
	if (InputManager->isOnceKeyDown(VK_RETURN) && m_alpha <= 0)
		SCENE->changeScene("����������");
}
