#pragma once
#include "Cobject.h"
class CNPC : public Cobject
{
private:
	RECT m_garNorRc; //¿¹½Ã
	image* m_garNorImage;
	animation* m_garNorAni;
	int m_garNorX;
	int m_garNorY;

	RECT m_shopKeeperRc;
	image* m_shopKeeperImage;
	animation* m_shopKeeperAni;
	int m_shopKeeperX;
	int m_shopKeeperY;

	RECT m_blackMarketRc;
	image* m_blackMarketImage;
	animation* m_blackMarketAni;
	int m_blackMarketX;
	int m_blackMarketY;

	RECT m_edwardRc;
	image* m_edwardImage;
	animation* m_edwardAni;
	int m_edwardX;
	int m_edwardY;

	RECT m_ericRc;
	image* m_ericImage;
	animation* m_ericAni;
	int m_ericX;
	int m_ericY;

	RECT m_halsteinRc;
	image* m_halsteinImage;
	animation* m_halsteinAni;
	int m_halsteinX;
	int m_halsteinY;

	RECT m_kaylaRc;
	image* m_kaylaImage;
	animation* m_kaylaAni;
	int m_kaylaX;
	int m_kaylaY;

	RECT m_sarcasterRc;
	image* m_sarcasterImage;
	animation* m_sarcasterAni;
	int m_sarcasterX;
	int m_sarcasterY;

	RECT m_torsteinRc;
	image* m_torsteinImage;
	animation* m_torsteinAni;
	int m_torsteinX;
	int m_torsteinY;

	RECT m_witchRc;
	image* m_witchImage;
	animation* m_witchAni;
	int m_witchX;
	int m_witchY;

	animation* m_healingcrossAni;

	bool m_isAni;
public:
	HRESULT init();
	void release();
	void update();
	void render();
	void getNpcAni();
	void getNpcRectangle();

	RECT* getGaNorRect() { return &m_garNorRc; }
	RECT* getShopKeeperRect() { return &m_shopKeeperRc; }
	RECT* getBlackMarketRect() { return &m_blackMarketRc; }
	RECT* getEdwardRect() { return &m_edwardRc; }
	RECT* getEricRect() { return &m_ericRc; }
	RECT* getHalsteinRect() { return &m_halsteinRc; }
	RECT* getKaylaRect() { return &m_kaylaRc; }
	RECT* getSarcasterRect() { return &m_sarcasterRc; }
	RECT* getTorsteinRect() { return &m_torsteinRc; }
	RECT* getWitchRect() { return &m_witchRc; }

};

