#pragma once
#include "gameNode.h"

struct stats
{
	int atk;
	int def;
	int hp;
	int mp;
	int lv;
	int exp;
	int gold;
	float speed;
};

class Cunit :public gameNode
{
protected:
	stats m_stats;
	RECT m_rc;
	float m_x, m_y;
	
public:
	Cunit();
	Cunit(float x, float y, RECT rc, stats stats);
	~Cunit();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//================ get ================//
	int getAtk() { return m_stats.atk; }
	int getDef() { return m_stats.def; }
	int getHp() { return m_stats.hp; }
	int getMp() { return m_stats.mp; }
	int getLv() { return m_stats.lv; }
	int getExp() { return m_stats.exp; }
	int getGold() { return m_stats.gold; }
	float getSpeed() { return m_stats.speed; }
	float getX() { return m_x; }
	float getY() { return m_y; }

	//================ set ================//
	void setAtk(int atk) { m_stats.atk = atk; }
	void setDef(int def) { m_stats.def = def; }
	void setHp(int hp) { m_stats.hp = hp; }
	void setMp(int mp) { m_stats.mp = mp; }
	void setLv(int lv) { m_stats.lv = lv; }
	void setExp(int exp) { m_stats.exp = exp; }
	void setGold(int gold) { m_stats.gold = gold; }
	void setSpeed(float speed) { m_stats.speed = speed; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
};

