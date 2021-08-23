#pragma once
#include "gameNode.h"
#include "Ctown.h"
#include "CplayerManager.h"
#include "camera.h"
#include "CaStar.h"
#include "CshopUi.h"
#include "CplayerData.h"
#include "CNPC.h"
#include "Cquest.h"
class CsceneTown : public gameNode
{
private:
	Ctown* m_town;
	camera* m_camera;
	CplayerManager* m_player;
	CaStar* m_aStar;
	Cshop* m_shop;
	CshopUi* m_shopUi;
	CplayerData* m_playerData;

	CNPC* m_npc;
	Cquest* m_quest;
private:
	RECT m_changeRect;
	RECT m_shopRect;
	RECT m_npcRect;
	bool isShopOn;

	bool isNpcCollison;

	float m_timerHp;
	float m_timerMp;

	RECT m_wingRect;
	image* m_wingImage;
	animation* m_wingAni;
	RECT m_wingShadowRect;
	image* m_wingShadowImage;
	animation* m_wingShadowAni;
	int m_wingX[2], m_wingY[2];

	// ±‚≈∏
	image* m_buttonImage;
	RECT m_buttonRc;

	int m_x;
	int m_y;
	bool isMessageRender;

public:
	CsceneTown();
	~CsceneTown();

	HRESULT init();
	void release();
	void update();
	void render();

	void sceneChange();
	void shopOn();
	void npcCollison();

	void setPlayerMemory(CplayerData* playerdata){ m_playerData = playerdata;}
	void setQuestMemory(Cquest* questdata) { m_quest = questdata; }

	void shopCollision();
};