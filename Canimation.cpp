#include "framework.h"
#include "Canimation.h"

Canimation::Canimation()
{
}

Canimation::~Canimation()
{
}

HRESULT Canimation::init()
{
	ANIMATION->addAnimation("��������", "�������̵�", 0, 2, 8, false, true);
	ANIMATION->addAnimation("��������", "�������̵�", 5, 7, 8, false, true);
	ANIMATION->addAnimation("��������", "�������̵�", 10, 12, 8, false, true);
	ANIMATION->addAnimation("��������", "�������̵�", 15, 17, 8, false, true);
	ANIMATION->addAnimation("����������", "�������̵�", 20, 22, 8, false, true);
	ANIMATION->addAnimation("�������»�", "�������̵�", 25, 27, 8, false, true);
	ANIMATION->addAnimation("����������", "�������̵�", 30, 32, 8, false, true);
	ANIMATION->addAnimation("���������", "�������̵�", 35, 37, 8, false, true);

	ANIMATION->addDefAnimation("����������", "������������", 2, false, true);
	ANIMATION->addDefAnimation("��ġ����", "��ġ������", 2, false, true);
	ANIMATION->addDefAnimation("���Ļ���", "���ľ�����", 2, false, true);

	ANIMATION->addAnimation("��������", "�����̵�", 0, 2, 5, false, true);
	ANIMATION->addAnimation("�����»�", "�����̵�", 3, 5, 5, false, true);

	ANIMATION->addAnimation("�����ź�������", "�����ź����̵�", 0, 2, 5, false, true);
	ANIMATION->addAnimation("�����ź����»�", "�����ź����̵�", 3, 5, 5, false, true);

	ANIMATION->addAnimation("���õ�������", "���õ����̵�", 0, 2, 5, false, true);
	ANIMATION->addAnimation("���õ����»�", "���õ����̵�", 3, 5, 5, false, true);
	return S_OK;
}
