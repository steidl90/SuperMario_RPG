#pragma once
#include "Ccharacter.h"
class Cmario :public Ccharacter
{
private:
	MOVE_TYPE direction;
	animation* m_ani;
	char str[20];

	int m_sceneNum;

	float prevX;
	float prevY;

public:
	Cmario();
	Cmario(float x, float y, RECT rc, stats stats);
	~Cmario();

	HRESULT init();
	void release();
	void update();
	void render();

	void move();
	void animation();
	void pixelCollision();

	virtual void run();
	virtual void attack();
	void item();
	void special();
	void etc();

	RECT* getRect() { return &m_rc; }

	int getSceneNum() { return m_sceneNum; }
	void setSceneNum(int num) { m_sceneNum = num; }

	bool getisFight() { return isFight; }
};