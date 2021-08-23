#include "framework.h"
#include "CsceneSelect.h"

CsceneSelect::CsceneSelect(): isSelect(true), fps(8)
{
}

CsceneSelect::~CsceneSelect()
{
}

HRESULT CsceneSelect::init()
{
	ANIMATION->addDefAnimation("아마존", "선택아마존", fps, false, true);
	m_ani[0] = ANIMATION->findAnimation("아마존");

	ANIMATION->addDefAnimation("데몬", "선택데몬", fps, false, true);
	m_ani[1] = ANIMATION->findAnimation("데몬");

	ANIMATION->addDefAnimation("데몬슬레이어", "선택데몬슬레이어", fps, false, true);
	m_ani[2] = ANIMATION->findAnimation("데몬슬레이어");

	ANIMATION->addDefAnimation("랜서", "선택랜서", fps, false, true);
	m_ani[3] = ANIMATION->findAnimation("랜서");

	ANIMATION->addDefAnimation("머로더", "선택머로더", fps, false, true);
	m_ani[4] = ANIMATION->findAnimation("머로더");

	ANIMATION->addDefAnimation("마크맨", "선택마크맨", fps, false, true);
	m_ani[5] = ANIMATION->findAnimation("마크맨");

	ANIMATION->addDefAnimation("네크로맨서", "선택네크로맨서", fps, false, true);
	m_ani[6] = ANIMATION->findAnimation("네크로맨서");

	ANIMATION->addDefAnimation("노마드", "선택노마드", fps, false, true);
	m_ani[7] = ANIMATION->findAnimation("노마드");

	ANIMATION->addDefAnimation("팔라딘", "선택팔라딘", fps, false, true);
	m_ani[8] = ANIMATION->findAnimation("팔라딘");

	ANIMATION->addDefAnimation("파이렛", "선택파이렛", fps, false, true);
	m_ani[9] = ANIMATION->findAnimation("파이렛");

	ANIMATION->addDefAnimation("레드넥", "선택레드넥", fps, false, true);
	m_ani[10] = ANIMATION->findAnimation("레드넥");

	ANIMATION->addDefAnimation("사무라이", "선택사무라이", fps, false, true);
	m_ani[11] = ANIMATION->findAnimation("사무라이");

	ANIMATION->addDefAnimation("샤먼", "선택샤먼", fps, false, true);
	m_ani[12] = ANIMATION->findAnimation("샤먼");

	ANIMATION->addDefAnimation("스틱맨", "선택스틱맨", fps, false, true);
	m_ani[13] = ANIMATION->findAnimation("스틱맨");

	ANIMATION->addDefAnimation("화이트메이지", "선택화이트메이지", fps, false, true);
	m_ani[14] = ANIMATION->findAnimation("화이트메이지");

	m_playerRc[0] = RectMakeCenter(400, 250, IMAGE->findImage("선택아마존")->getFrameWidth(), IMAGE->findImage("선택아마존")->getFrameHeight());
	m_playerRc[1] = RectMakeCenter(520, 250, IMAGE->findImage("선택데몬")->getFrameWidth(), IMAGE->findImage("선택데몬")->getFrameHeight());
	m_playerRc[2] = RectMakeCenter(640, 250, IMAGE->findImage("선택데몬슬레이어")->getFrameWidth(), IMAGE->findImage("선택데몬슬레이어")->getFrameHeight());
	m_playerRc[3] = RectMakeCenter(760, 265, IMAGE->findImage("선택랜서")->getFrameWidth(), IMAGE->findImage("선택랜서")->getFrameHeight());
	m_playerRc[4] = RectMakeCenter(900, 250, IMAGE->findImage("선택머로더")->getFrameWidth(), IMAGE->findImage("선택머로더")->getFrameHeight());

	m_playerRc[5] = RectMakeCenter(400, 400, IMAGE->findImage("선택마크맨")->getFrameWidth(), IMAGE->findImage("선택마크맨")->getFrameHeight());
	m_playerRc[6] = RectMakeCenter(520, 400, IMAGE->findImage("선택네크로맨서")->getFrameWidth(), IMAGE->findImage("선택네크로맨서")->getFrameHeight());
	m_playerRc[7] = RectMakeCenter(640, 400, IMAGE->findImage("선택노마드")->getFrameWidth(), IMAGE->findImage("선택노마드")->getFrameHeight());
	m_playerRc[8] = RectMakeCenter(760, 400, IMAGE->findImage("선택팔라딘")->getFrameWidth(), IMAGE->findImage("선택팔라딘")->getFrameHeight());
	m_playerRc[9] = RectMakeCenter(880, 400, IMAGE->findImage("선택파이렛")->getFrameWidth(), IMAGE->findImage("선택파이렛")->getFrameHeight());

	m_playerRc[10] = RectMakeCenter(385, 550, IMAGE->findImage("선택레드넥")->getFrameWidth(), IMAGE->findImage("선택레드넥")->getFrameHeight());
	m_playerRc[11] = RectMakeCenter(505, 535, IMAGE->findImage("선택사무라이")->getFrameWidth(), IMAGE->findImage("선택사무라이")->getFrameHeight());
	m_playerRc[12] = RectMakeCenter(640, 555, IMAGE->findImage("선택샤먼")->getFrameWidth(), IMAGE->findImage("선택샤먼")->getFrameHeight());
	m_playerRc[13] = RectMakeCenter(760, 550, IMAGE->findImage("선택스틱맨")->getFrameWidth(), IMAGE->findImage("선택스틱맨")->getFrameHeight());
	m_playerRc[14] = RectMakeCenter(880, 550, IMAGE->findImage("선택화이트메이지")->getFrameWidth(), IMAGE->findImage("선택화이트메이지")->getFrameHeight());

	return S_OK;
}

void CsceneSelect::release()
{
}

void CsceneSelect::update()
{
	animation();
	sceneChange();
}

void CsceneSelect::render()
{
	this->getMapBuffer()->render(getMemDC(), 0, 0);
	imageRender();
}

void CsceneSelect::animation()
{
	if (isSelect)
	{
		ANIMATION->start("아마존");
		ANIMATION->start("데몬");
		ANIMATION->start("데몬슬레이어");
		ANIMATION->start("랜서");
		ANIMATION->start("머로더");

		ANIMATION->start("마크맨");
		ANIMATION->start("네크로맨서");
		ANIMATION->start("노마드");
		ANIMATION->start("팔라딘");
		ANIMATION->start("파이렛");

		ANIMATION->start("레드넥");
		ANIMATION->start("사무라이");
		ANIMATION->start("샤먼");
		ANIMATION->start("스틱맨");
		ANIMATION->start("화이트메이지");

		isSelect = false;
	}
}

void CsceneSelect::imageRender()
{
	IMAGE->render("선택씬배경", getMapDC());
	shadowEffect();
	selectEffect();
	IMAGE->findImage("선택아마존")->aniRender(getMapDC(), m_playerRc[0].left, m_playerRc[0].top, m_ani[0]);
	IMAGE->findImage("선택데몬")->aniRender(getMapDC(), m_playerRc[1].left, m_playerRc[1].top, m_ani[1]);
	IMAGE->findImage("선택데몬슬레이어")->aniRender(getMapDC(), m_playerRc[2].left, m_playerRc[2].top, m_ani[2]);
	IMAGE->findImage("선택랜서")->aniRender(getMapDC(), m_playerRc[3].left, m_playerRc[3].top, m_ani[3]);
	IMAGE->findImage("선택머로더")->aniRender(getMapDC(), m_playerRc[4].left, m_playerRc[4].top, m_ani[4]);

	IMAGE->findImage("선택마크맨")->aniRender(getMapDC(), m_playerRc[5].left, m_playerRc[5].top, m_ani[5]);
	IMAGE->findImage("선택네크로맨서")->aniRender(getMapDC(), m_playerRc[6].left, m_playerRc[6].top, m_ani[6]);
	IMAGE->findImage("선택노마드")->aniRender(getMapDC(), m_playerRc[7].left, m_playerRc[7].top, m_ani[7]);
	IMAGE->findImage("선택팔라딘")->aniRender(getMapDC(), m_playerRc[8].left, m_playerRc[8].top, m_ani[8]);
	IMAGE->findImage("선택파이렛")->aniRender(getMapDC(), m_playerRc[9].left, m_playerRc[9].top, m_ani[9]);

	IMAGE->findImage("선택레드넥")->aniRender(getMapDC(), m_playerRc[10].left, m_playerRc[10].top, m_ani[10]);
	IMAGE->findImage("선택사무라이")->aniRender(getMapDC(), m_playerRc[11].left, m_playerRc[11].top, m_ani[11]);
	IMAGE->findImage("선택샤먼")->aniRender(getMapDC(), m_playerRc[12].left, m_playerRc[12].top, m_ani[12]);
	IMAGE->findImage("선택스틱맨")->aniRender(getMapDC(), m_playerRc[13].left, m_playerRc[13].top, m_ani[13]);
	IMAGE->findImage("선택화이트메이지")->aniRender(getMapDC(), m_playerRc[14].left, m_playerRc[14].top, m_ani[14]);
}

void CsceneSelect::sceneChange()
{
	if (PtInRect(&m_playerRc[0], m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) SCENE->changeScene("마을");
}

void CsceneSelect::shadowEffect()
{
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 387, 255, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 500, 259, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 620, 263, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 748, 260, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 859, 257, 150);

	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 385, 415, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 500, 417, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 623, 415, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 742, 413, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 859, 416, 150);

	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 384, 566, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 501, 567, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 622, 565, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 743, 577, 150);
	IMAGE->findImage("선택그림자")->alphaRender(getMapDC(), 867, 567, 150);
}

void CsceneSelect::selectEffect()
{
	if (PtInRect(&m_playerRc[0], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 385, 255);
	else if (PtInRect(&m_playerRc[1], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 498, 259);
	else if (PtInRect(&m_playerRc[2], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 618, 263);
	else if (PtInRect(&m_playerRc[3], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 746, 260);
	else if (PtInRect(&m_playerRc[4], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 857, 257);
	else if (PtInRect(&m_playerRc[5], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 383, 415);
	else if (PtInRect(&m_playerRc[6], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 498, 417);
	else if (PtInRect(&m_playerRc[7], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 621, 415);
	else if (PtInRect(&m_playerRc[8], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 740, 413);
	else if (PtInRect(&m_playerRc[9], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 857, 416);
	else if (PtInRect(&m_playerRc[10], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 382, 566);
	else if (PtInRect(&m_playerRc[11], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 499, 567);
	else if (PtInRect(&m_playerRc[12], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 620, 565);
	else if (PtInRect(&m_playerRc[13], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 741, 577);
	else if (PtInRect(&m_playerRc[14], m_ptMouse)) IMAGE->findImage("선택효과")->render(getMapDC(), 865, 567);
}
