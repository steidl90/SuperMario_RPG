#pragma once
#include "gameNode.h"
#include "Cmario.h"
#include "CsceneTitle.h"
#include "CsceneTown.h"
#include "CsceneMarioHouse.h"
#include "CsceneBanditsWay.h"
#include "CsceneBattle.h"
#include "CsceneEnding.h"
#include "Cmonster.h"
#include "CmonsterFactory.h"
class mainGame : public gameNode
{
private:

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	RECT checkGameSize();
};
