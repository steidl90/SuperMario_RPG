#include "framework.h"
#include "CsceneTitle.h"

CsceneTitle::CsceneTitle()
{
}

HRESULT CsceneTitle::init()
{
    m_alpha = 255;
    return S_OK;
}

void CsceneTitle::update()
{
    if (m_alpha > 0)
        m_alpha -= 5;
    sceneChange();
}

void CsceneTitle::render()
{
    ZORDER->zorderRender(IMAGE->findImage("Ÿ��Ʋ"), ZMAP, 0, 0, 0);
    if (m_alpha > 0)
        ZORDER->zorderAlphaRender(IMAGE->findImage("����"), ZMAP, 1, 0, 0, m_alpha);
}

void CsceneTitle::sceneChange()
{
    if (InputManager->isOnceKeyDown(VK_RETURN) && m_alpha <= 0)
        SCENE->changeScene("����������");
}
