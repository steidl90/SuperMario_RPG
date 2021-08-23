#pragma once
#include"gameNode.h"
#include"Cinventory.h"
// 인벤토리 include 오류나면 전방참조

class Cplayer;
class CinventoryUi : public gameNode
{
private:
	Cinventory* m_Inventory;
	Cplayer* m_player;

private:

	// 기본 UI 멤버변수
	RECT m_InventoryRect;
	int m_uiX;
	int m_uiY;
	int m_itemListX;
	int m_itemListY;
	int m_EquipItemX;
	int m_EquipItemY;
	int m_itemInfoX;
	int m_itemInfoY;
	int m_functionButtonX;
	int m_functionButtonY;

	vector<RECT> m_vItemListRect;
	vector<RECT> m_vEquipItemSubRect;
	vector<RECT> m_vEquipItemMainRect;
	RECT m_ItemInfoRect;

	RECT m_equipButton;
	RECT m_abandonButton;

	// 버튼 클릭시 stay다운을 once처럼 쓰기위해..
	bool isButtonClick;
	bool isKeyUp;

	// 기능 구현 멤버변수
	ITEMTYPE m_selectType;
	//Citem* m_selectItem;
	Citem m_itemInit[5];
	// 구조 수정
	EquipItem m_equipItem[5];

	int m_showIndex;
	int m_showEndIndex;
	int m_selectRenderX;
	int m_selectRenderY;
	int m_equipRenderX;
	int m_equipRenderY;
	int m_clickCount;

	bool isSelectRender;
	int m_SelectIndex;
	int m_compareTime;

	RECT m_clickCheckRect;

	POINT m_equipRenderPoint[5];  // 필요없는 변수인데 이걸 없애면 오류가 나네... ???

public:

	CinventoryUi();
	~CinventoryUi();

	HRESULT init();
	void release();
	void update();
	void render();

	// 인벤토리 정보 set
	void setInventoryMemory(Cinventory* inven) { m_Inventory = inven; }
	// 플레이어 정보 set
	void setPlayerMemory(Cplayer* player) { m_player = player; }

	// 타입이 정해졌을때 설정된 리스트의 showIndex (보여줄 인덱스 범위) 설정
	void setShowIndex();

	// 타입별 아이템 출력
	void showListItemType();
	void showItemList(vector<Citem*>* list);

	// 장착 테두리 출력
	void showEquipSelect();

	// 리스트에서 선택시 동작 / + 장착
	void selectItem();
	void selectEquipItem();

	// 아이템 장착 동작!
	void setPlayerStat(int index);
	void clickEquipButton();
	// 장비창 rect 클릭시 선택 아이템 타입 변경
	void selectItemTypeMain();
	void selectItemTypeSub();

	// 아이템 상세정보 창
	void showItemInfo();
	void showItemCompare();

	// 아이템 버리기 동작
	void abandonItem();

	// 아이템 해제 동작
	void unEquipItem();
	
	// 포션 선택
	void selectPotion();
	void showPotionInfo();
};

