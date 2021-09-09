#include "framework.h"
#include "CsceneEnding.h"

CsceneEnding::CsceneEnding()
{
}

HRESULT CsceneEnding::init()
{
	m_alpha = 255;
	ANIMATION->start("감사엔딩");
	ANIMATION->start("마리오엔딩");
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
	ZORDER->zorderRender(IMAGE->findImage("엔딩배경"), ZMAP, 0, 0, 0);
	ZORDER->zorderAniRender(IMAGE->findImage("엔딩감사"), ZMAP, 1, 0, 0, ANIMATION->findAnimation("감사엔딩"));
	ZORDER->zorderAniRender(IMAGE->findImage("엔딩마리오"), ZMAP, 1, WINSIZEX / 2 - 150, WINSIZEY - 300, ANIMATION->findAnimation("마리오엔딩"));

	if (m_alpha > 0)
		ZORDER->zorderAlphaRender(IMAGE->findImage("알파"), ZMAP, 2, 0, 0, m_alpha);
}

void CsceneEnding::sceneChange()
{
	if (InputManager->isOnceKeyDown(VK_RETURN) && m_alpha <= 0)
		SCENE->changeScene("마리오의집");
}
