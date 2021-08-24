#include "framework.h"
#include "Cimage.h"

Cimage::Cimage()
{
}

Cimage::~Cimage()
{
}

HRESULT Cimage::init()
{
	m_vImageList = TXT->txtLoad("�̹�������Ʈ.csv");

	//=================Player=================//
	IMAGE->addImage("���������", "images/Mario_idle.bmp", 24, 34, true, RGB(255, 0, 255));
	IMAGE->addImage("��ġ���", "images/Peach_adle.bmp", 24, 34, true, RGB(255, 0, 255));
	IMAGE->addImage("���Ĵ��", "images/Bowser_idle.bmp", 34, 44, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("�������̵�", "images/Mario_move.bmp", 140, 295, 5, 8, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("����������", "images/Mario_attack.bmp", 245, 79, 7, 2, true, RGB(255, 0, 255));

	//=================NPC====================//


	//=================Enemy=================//
	IMAGE->addFrameImage("�����̵�", "images/Goomba_move.bmp", 75, 50, 3, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("���ٰ���", "images/Goomba_attack.bmp", 250, 25, 10, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("���õ����̵�", "images/Spikey_move.bmp", 90, 60, 3, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("���õ��̰���", "images/Spikey_attack.bmp", 150, 30, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("�����ź����̵�", "images/SkyTroopa_move.bmp", 105, 75, 3, 2, true, RGB(255, 0, 255));
	//IMAGE->addFrameImage("�����ź��̰���", "images/SkyTroopa_move.bmp", 105, 75, 3, 1, true, RGB(255, 0, 255));


	//=================Boss==================//



	//=================Object=================//
	IMAGE->addFrameImage("ū����", "images/BigCoin_Effect.bmp", 544, 34, 16, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("��������", "images/SmallCoin_Effect.bmp", 544, 34, 16, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("���̺����", "images/SaveBox.bmp", 141, 35, 4, 1, true, RGB(255, 0, 255));


	//=================Map=================//
	IMAGE->addImage("�ʵ��1", "images/BanditsWay_Map.bmp", 800, 576, true, RGB(255, 0, 255));
	IMAGE->addImage("�ʵ��2", "images/BanditsWay_Map1.bmp", 800, 388, true, RGB(255, 0, 255));
	IMAGE->addImage("������", "images/Town_Map.bmp", 809, 717, true, RGB(255, 0, 255));
	IMAGE->addImage("��Ʋ��1", "images/Battle_Map.bmp", 256, 222, true, RGB(255, 0, 255));
	IMAGE->addImage("��Ʋ��2", "images/Battle_Map2.bmp", 256, 222, true, RGB(255, 0, 255));
	IMAGE->addImage("�����1", "images/World_Map1.bmp", 199, 208, true, RGB(255, 0, 255));
	IMAGE->addImage("�����2", "images/World_Map2.bmp", 199, 208, true, RGB(255, 0, 255));
	IMAGE->addImage("�����3", "images/World_Map3.bmp", 199, 208, true, RGB(255, 0, 255));


	//==================UI==================//
	IMAGE->addImage("������UI", "images/LevelUP_UI.bmp", 256, 256, true, RGB(255, 0, 255));
	IMAGE->addImage("���������", "images/LevelUP_bg.bmp", 256, 256, true, RGB(255, 0, 255));
	IMAGE->addImage("�÷��̾�޴�", "images/Player_Menu.bmp", 256, 256, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("������������", "images/Mario_icon.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("��ġ������", "images/Peach_icon.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("���ľ�����", "images/Bowser_icon.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("����������", "images/LevelUP_Select.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("����������", "images/LevelUP_stats.bmp", 96, 96, 3, 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("��������", "images/LevelUP_flower.bmp", 160, 40, 4, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("���������ʽ�", "images/LevelUP_Bonus.bmp", 264, 72, 3, 1, true, RGB(255, 0, 255));


	//==================ECT=================//



	return S_OK;
}

void Cimage::release()
{
}

void Cimage::update()
{
}

void Cimage::render()
{
}

void Cimage::initImg()
{
	for (int i = 0; i < m_vImageList.size(); i += 12)
	{
		//if()m_Type
		m_imageUrl = m_vImageList[i + 1];
	}
}
