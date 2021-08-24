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
	//=================Player=================//
	IMAGE->addImage("마리오대기", "images/Mario_idle.bmp", 24, 34, true, RGB(255, 0, 255));
	IMAGE->addImage("피치대기", "images/Peach_adle.bmp", 24, 34, true, RGB(255, 0, 255));
	IMAGE->addImage("쿠파대기", "images/Bowser_idle.bmp", 34, 44, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("마리오이동", "images/Mario_move.bmp", 140, 295, 5, 8, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("마리오공격", "images/Mario_attack.bmp", 245, 79, 7, 2, true, RGB(255, 0, 255));

	//=================NPC====================//


	//=================Enemy=================//
	IMAGE->addFrameImage("굼바이동", "images/Goomba_move.bmp", 75, 50, 3, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("굼바공격", "images/Goomba_attack.bmp", 250, 25, 10, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("가시돌이이동", "images/Spikey_move.bmp", 90, 60, 3, 2, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("가시돌이공격", "images/Spikey_attack.bmp", 150, 30, 5, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("날개거북이이동", "images/SkyTroopa_move.bmp", 105, 75, 3, 2, true, RGB(255, 0, 255));
	//IMAGE->addFrameImage("날개거북이공격", "images/SkyTroopa_move.bmp", 105, 75, 3, 1, true, RGB(255, 0, 255));


	//=================Boss==================//



	//=================Object=================//
	IMAGE->addFrameImage("큰코인", "images/BigCoin_Effect.bmp", 544, 34, 16, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("작은코인", "images/SmallCoin_Effect.bmp", 544, 34, 16, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("세이브상자", "images/SaveBox.bmp", 141, 35, 4, 1, true, RGB(255, 0, 255));


	//=================Map=================//
	IMAGE->addImage("필드맵1", "images/BanditsWay_Map.bmp", 800, 576, true, RGB(255, 0, 255));
	IMAGE->addImage("필드맵2", "images/BanditsWay_Map1.bmp", 800, 388, true, RGB(255, 0, 255));
	IMAGE->addImage("마을맵", "images/Town_Map.bmp", 809, 717, true, RGB(255, 0, 255));
	IMAGE->addImage("배틀맵1", "images/Battle_Map.bmp", 256, 222, true, RGB(255, 0, 255));
	IMAGE->addImage("배틀맵2", "images/Battle_Map2.bmp", 256, 222, true, RGB(255, 0, 255));
	IMAGE->addImage("월드맵1", "images/World_Map1.bmp", 199, 208, true, RGB(255, 0, 255));
	IMAGE->addImage("월드맵2", "images/World_Map2.bmp", 199, 208, true, RGB(255, 0, 255));
	IMAGE->addImage("월드맵3", "images/World_Map3.bmp", 199, 208, true, RGB(255, 0, 255));


	//==================UI==================//
	IMAGE->addImage("레벨업UI", "images/LevelUP_UI.bmp", 256, 256, true, RGB(255, 0, 255));
	IMAGE->addImage("레벨업배경", "images/LevelUP_bg.bmp", 256, 256, true, RGB(255, 0, 255));
	IMAGE->addImage("플레이어메뉴", "images/Player_Menu.bmp", 256, 256, true, RGB(255, 0, 255));

	IMAGE->addFrameImage("마리오아이콘", "images/Mario_icon.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("피치아이콘", "images/Peach_icon.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("쿠파아이콘", "images/Bowser_icon.bmp", 90, 30, 3, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("레벨업선택", "images/LevelUP_Select.bmp", 192, 48, 4, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("레벨업스탯", "images/LevelUP_stats.bmp", 96, 96, 3, 3, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("레벨업꽃", "images/LevelUP_flower.bmp", 160, 40, 4, 1, true, RGB(255, 0, 255));
	IMAGE->addFrameImage("레벨업보너스", "images/LevelUP_Bonus.bmp", 264, 72, 3, 1, true, RGB(255, 0, 255));


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
