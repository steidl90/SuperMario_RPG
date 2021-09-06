#pragma once
#include "gameNode.h"

struct stats
{
	int atk;
	int def;
	int hp;
	int maxHp;
	int mp;
	int maxMp;
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
	bool isFight;
	MONSTER_TYPE m_unitType;
	CHARACTER_TYPE m_type;

public:
	Cunit();
	Cunit(float x, float y, RECT rc, stats stats);
	~Cunit() = default;

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void attack() = 0;
	virtual void move() = 0;

	//================ get ================//
	int getAtk() { return m_stats.atk; }
	int getDef() { return m_stats.def; }
	int getHp() { return m_stats.hp; }
	int getMaxHp() { return m_stats.maxHp; }
	int getMp() { return m_stats.mp; }
	int getMaxMp() { return m_stats.maxMp; }
	int getLv() { return m_stats.lv; }
	int getExp() { return m_stats.exp; }
	int getGold() { return m_stats.gold; }
	float getSpeed() { return m_stats.speed; }
	float getX() { return m_x; }
	float getY() { return m_y; }
	RECT getRect() { return m_rc; }
	//CHARACTER_TYPE getCharacterType() { return m_type; }
	bool getisFight() { return isFight; }

	//================ set ================//
	void setAtk(int atk) { m_stats.atk = atk; }
	void setDef(int def) { m_stats.def = def; }
	void setHp(int hp) { m_stats.hp = hp; }
	void setMaxHp(int maxhp) { m_stats.maxHp = maxhp; }
	void setMp(int mp) { m_stats.mp = mp; }
	void setMaxMp(int maxmp) { m_stats.maxMp = maxmp; }
	void setLv(int lv) { m_stats.lv = lv; }
	void setExp(int exp) { m_stats.exp = exp; }
	void setGold(int gold) { m_stats.gold = gold; }
	void setSpeed(float speed) { m_stats.speed = speed; }
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setRect(RECT rc) { m_rc = rc; }
	//void setCharacterType(CHARACTER_TYPE type) { m_type = type; }
	void setisFight(bool fight) { isFight = fight; }
};

