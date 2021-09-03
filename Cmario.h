#pragma once
#include "Cunit.h"
#include "CFSMController.h"
class Cmario :public Cunit
{
private:
	MOVE_TYPE direction;
	animation* m_ani;
	char str[20];

	int m_sceneNum;
	int m_beforeSceneNum;

	float prevX;
	float prevY;

	CFSMController* m_FSM;

public:
	Cmario();
	Cmario(float x, float y, RECT rc, stats stats);
	~Cmario();

	HRESULT init();
	void release();
	void update();
	void render();

	void run();
	void animation();
	void pixelCollision();

	virtual void move();
	virtual void attack();
	void item();
	void special();
	void etc();

	RECT* getRect() { return &m_rc; }

	int getSceneNum() { return m_sceneNum; }
	void setSceneNum(int num) { m_sceneNum = num; }
	
	int getBeforeSceneNum() { return m_beforeSceneNum; }
	void setBeforeSceneNum(int num) { m_beforeSceneNum = num; }

	bool getisFight() { return isFight; }
};