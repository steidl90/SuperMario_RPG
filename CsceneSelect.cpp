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
	ANIMATION->addDefAnimation("�Ƹ���", "���þƸ���", fps, false, true);
	m_ani[0] = ANIMATION->findAnimation("�Ƹ���");

	ANIMATION->addDefAnimation("����", "���õ���", fps, false, true);
	m_ani[1] = ANIMATION->findAnimation("����");

	ANIMATION->addDefAnimation("���󽽷��̾�", "���õ��󽽷��̾�", fps, false, true);
	m_ani[2] = ANIMATION->findAnimation("���󽽷��̾�");

	ANIMATION->addDefAnimation("����", "���÷���", fps, false, true);
	m_ani[3] = ANIMATION->findAnimation("����");

	ANIMATION->addDefAnimation("�ӷδ�", "���øӷδ�", fps, false, true);
	m_ani[4] = ANIMATION->findAnimation("�ӷδ�");

	ANIMATION->addDefAnimation("��ũ��", "���ø�ũ��", fps, false, true);
	m_ani[5] = ANIMATION->findAnimation("��ũ��");

	ANIMATION->addDefAnimation("��ũ�θǼ�", "���ó�ũ�θǼ�", fps, false, true);
	m_ani[6] = ANIMATION->findAnimation("��ũ�θǼ�");

	ANIMATION->addDefAnimation("�븶��", "���ó븶��", fps, false, true);
	m_ani[7] = ANIMATION->findAnimation("�븶��");

	ANIMATION->addDefAnimation("�ȶ��", "�����ȶ��", fps, false, true);
	m_ani[8] = ANIMATION->findAnimation("�ȶ��");

	ANIMATION->addDefAnimation("���̷�", "�������̷�", fps, false, true);
	m_ani[9] = ANIMATION->findAnimation("���̷�");

	ANIMATION->addDefAnimation("�����", "���÷����", fps, false, true);
	m_ani[10] = ANIMATION->findAnimation("�����");

	ANIMATION->addDefAnimation("�繫����", "���û繫����", fps, false, true);
	m_ani[11] = ANIMATION->findAnimation("�繫����");

	ANIMATION->addDefAnimation("����", "���û���", fps, false, true);
	m_ani[12] = ANIMATION->findAnimation("����");

	ANIMATION->addDefAnimation("��ƽ��", "���ý�ƽ��", fps, false, true);
	m_ani[13] = ANIMATION->findAnimation("��ƽ��");

	ANIMATION->addDefAnimation("ȭ��Ʈ������", "����ȭ��Ʈ������", fps, false, true);
	m_ani[14] = ANIMATION->findAnimation("ȭ��Ʈ������");

	m_playerRc[0] = RectMakeCenter(400, 250, IMAGE->findImage("���þƸ���")->getFrameWidth(), IMAGE->findImage("���þƸ���")->getFrameHeight());
	m_playerRc[1] = RectMakeCenter(520, 250, IMAGE->findImage("���õ���")->getFrameWidth(), IMAGE->findImage("���õ���")->getFrameHeight());
	m_playerRc[2] = RectMakeCenter(640, 250, IMAGE->findImage("���õ��󽽷��̾�")->getFrameWidth(), IMAGE->findImage("���õ��󽽷��̾�")->getFrameHeight());
	m_playerRc[3] = RectMakeCenter(760, 265, IMAGE->findImage("���÷���")->getFrameWidth(), IMAGE->findImage("���÷���")->getFrameHeight());
	m_playerRc[4] = RectMakeCenter(900, 250, IMAGE->findImage("���øӷδ�")->getFrameWidth(), IMAGE->findImage("���øӷδ�")->getFrameHeight());

	m_playerRc[5] = RectMakeCenter(400, 400, IMAGE->findImage("���ø�ũ��")->getFrameWidth(), IMAGE->findImage("���ø�ũ��")->getFrameHeight());
	m_playerRc[6] = RectMakeCenter(520, 400, IMAGE->findImage("���ó�ũ�θǼ�")->getFrameWidth(), IMAGE->findImage("���ó�ũ�θǼ�")->getFrameHeight());
	m_playerRc[7] = RectMakeCenter(640, 400, IMAGE->findImage("���ó븶��")->getFrameWidth(), IMAGE->findImage("���ó븶��")->getFrameHeight());
	m_playerRc[8] = RectMakeCenter(760, 400, IMAGE->findImage("�����ȶ��")->getFrameWidth(), IMAGE->findImage("�����ȶ��")->getFrameHeight());
	m_playerRc[9] = RectMakeCenter(880, 400, IMAGE->findImage("�������̷�")->getFrameWidth(), IMAGE->findImage("�������̷�")->getFrameHeight());

	m_playerRc[10] = RectMakeCenter(385, 550, IMAGE->findImage("���÷����")->getFrameWidth(), IMAGE->findImage("���÷����")->getFrameHeight());
	m_playerRc[11] = RectMakeCenter(505, 535, IMAGE->findImage("���û繫����")->getFrameWidth(), IMAGE->findImage("���û繫����")->getFrameHeight());
	m_playerRc[12] = RectMakeCenter(640, 555, IMAGE->findImage("���û���")->getFrameWidth(), IMAGE->findImage("���û���")->getFrameHeight());
	m_playerRc[13] = RectMakeCenter(760, 550, IMAGE->findImage("���ý�ƽ��")->getFrameWidth(), IMAGE->findImage("���ý�ƽ��")->getFrameHeight());
	m_playerRc[14] = RectMakeCenter(880, 550, IMAGE->findImage("����ȭ��Ʈ������")->getFrameWidth(), IMAGE->findImage("����ȭ��Ʈ������")->getFrameHeight());

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
		ANIMATION->start("�Ƹ���");
		ANIMATION->start("����");
		ANIMATION->start("���󽽷��̾�");
		ANIMATION->start("����");
		ANIMATION->start("�ӷδ�");

		ANIMATION->start("��ũ��");
		ANIMATION->start("��ũ�θǼ�");
		ANIMATION->start("�븶��");
		ANIMATION->start("�ȶ��");
		ANIMATION->start("���̷�");

		ANIMATION->start("�����");
		ANIMATION->start("�繫����");
		ANIMATION->start("����");
		ANIMATION->start("��ƽ��");
		ANIMATION->start("ȭ��Ʈ������");

		isSelect = false;
	}
}

void CsceneSelect::imageRender()
{
	IMAGE->render("���þ����", getMapDC());
	shadowEffect();
	selectEffect();
	IMAGE->findImage("���þƸ���")->aniRender(getMapDC(), m_playerRc[0].left, m_playerRc[0].top, m_ani[0]);
	IMAGE->findImage("���õ���")->aniRender(getMapDC(), m_playerRc[1].left, m_playerRc[1].top, m_ani[1]);
	IMAGE->findImage("���õ��󽽷��̾�")->aniRender(getMapDC(), m_playerRc[2].left, m_playerRc[2].top, m_ani[2]);
	IMAGE->findImage("���÷���")->aniRender(getMapDC(), m_playerRc[3].left, m_playerRc[3].top, m_ani[3]);
	IMAGE->findImage("���øӷδ�")->aniRender(getMapDC(), m_playerRc[4].left, m_playerRc[4].top, m_ani[4]);

	IMAGE->findImage("���ø�ũ��")->aniRender(getMapDC(), m_playerRc[5].left, m_playerRc[5].top, m_ani[5]);
	IMAGE->findImage("���ó�ũ�θǼ�")->aniRender(getMapDC(), m_playerRc[6].left, m_playerRc[6].top, m_ani[6]);
	IMAGE->findImage("���ó븶��")->aniRender(getMapDC(), m_playerRc[7].left, m_playerRc[7].top, m_ani[7]);
	IMAGE->findImage("�����ȶ��")->aniRender(getMapDC(), m_playerRc[8].left, m_playerRc[8].top, m_ani[8]);
	IMAGE->findImage("�������̷�")->aniRender(getMapDC(), m_playerRc[9].left, m_playerRc[9].top, m_ani[9]);

	IMAGE->findImage("���÷����")->aniRender(getMapDC(), m_playerRc[10].left, m_playerRc[10].top, m_ani[10]);
	IMAGE->findImage("���û繫����")->aniRender(getMapDC(), m_playerRc[11].left, m_playerRc[11].top, m_ani[11]);
	IMAGE->findImage("���û���")->aniRender(getMapDC(), m_playerRc[12].left, m_playerRc[12].top, m_ani[12]);
	IMAGE->findImage("���ý�ƽ��")->aniRender(getMapDC(), m_playerRc[13].left, m_playerRc[13].top, m_ani[13]);
	IMAGE->findImage("����ȭ��Ʈ������")->aniRender(getMapDC(), m_playerRc[14].left, m_playerRc[14].top, m_ani[14]);
}

void CsceneSelect::sceneChange()
{
	if (PtInRect(&m_playerRc[0], m_ptMouse) && InputManager->isOnceKeyDown(VK_LBUTTON)) SCENE->changeScene("����");
}

void CsceneSelect::shadowEffect()
{
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 387, 255, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 500, 259, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 620, 263, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 748, 260, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 859, 257, 150);

	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 385, 415, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 500, 417, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 623, 415, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 742, 413, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 859, 416, 150);

	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 384, 566, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 501, 567, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 622, 565, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 743, 577, 150);
	IMAGE->findImage("���ñ׸���")->alphaRender(getMapDC(), 867, 567, 150);
}

void CsceneSelect::selectEffect()
{
	if (PtInRect(&m_playerRc[0], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 385, 255);
	else if (PtInRect(&m_playerRc[1], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 498, 259);
	else if (PtInRect(&m_playerRc[2], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 618, 263);
	else if (PtInRect(&m_playerRc[3], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 746, 260);
	else if (PtInRect(&m_playerRc[4], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 857, 257);
	else if (PtInRect(&m_playerRc[5], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 383, 415);
	else if (PtInRect(&m_playerRc[6], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 498, 417);
	else if (PtInRect(&m_playerRc[7], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 621, 415);
	else if (PtInRect(&m_playerRc[8], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 740, 413);
	else if (PtInRect(&m_playerRc[9], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 857, 416);
	else if (PtInRect(&m_playerRc[10], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 382, 566);
	else if (PtInRect(&m_playerRc[11], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 499, 567);
	else if (PtInRect(&m_playerRc[12], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 620, 565);
	else if (PtInRect(&m_playerRc[13], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 741, 577);
	else if (PtInRect(&m_playerRc[14], m_ptMouse)) IMAGE->findImage("����ȿ��")->render(getMapDC(), 865, 567);
}
